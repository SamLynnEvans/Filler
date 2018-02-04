/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:31:57 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 18:56:37 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	build_borders(t_vis *v)
{
	int	x;
	int	y;
	int	tmp;

	y = 0;
	while (y <= v->size[Y] * v->height)
	{
		x = 0;
		while (x <= v->width * v->size[X])
		{
			tmp = x * 4 + y *v->sl;;
			v->data[tmp++] = 0xBD; 
			v->data[tmp++] = 0xBD; 
			v->data[tmp++] = 0xBD;
			x++;
		}
		y++;
	}
}

/*
void	add_mapkey(t_input *i)
{
	int x;

	x = (i->isize - 850) / 2;
	mlx_string_put(i->mlx, i->win, 30, 20, 0x000000,
	"- Slynn-ev homebrewed wire frame v1.0");
	mlx_string_put(i->mlx, i->win, x, i->isize - 47, 0x000000, "KEY");
	mlx_string_put(i->mlx, i->win, x + 80, i->isize - 60, 0x000000,
	"+ / - : zoom in / out");
	mlx_string_put(i->mlx, i->win, x + 80, i->isize - 35, 0x000000,
	"i / o : altitude up / down");
	mlx_string_put(i->mlx, i->win, x + 380, i->isize - 60, 0x000000,
	"< / >  : rotate up / down");
	mlx_string_put(i->mlx, i->win, x + 380, i->isize - 35, 0x000000,
	"arrows : move shape");
	mlx_string_put(i->mlx, i->win, x + 680, i->isize - 60, 0x000000,
	"  p   : colour peaks");
	mlx_string_put(i->mlx, i->win, x + 680, i->isize - 35, 0x000000,
	"c/v/b : colour +/-/0");
}
*/
void	put_to_image(t_vis *v, int x, int y, int color)
{
	int	pos;
	int	i;
	int	j;
	int	tmp;
	
	j = 0;
	pos = (x * 4 * v->width) + (y * v->sl * v->height) + 4 + v->sl;
	while (j++ < v->height - 1)
	{
		tmp = pos;
		i = 0;
		while (i++ < v->width - 1)
		{
			v->data[tmp++] = color;
			v->data[tmp++] = color >> 8;
			v->data[tmp++] = color >> 16;
			tmp++;
		}
		pos += v->sl;
	}
}

char	*copy_map(t_vis *v)
{
	int		i;
	char	*map_copy;

	i = 0;
	map_copy = malloc(sizeof(char) * v->size[X] * v->size[Y] + 1);
	while (i < v->size[X] * v->size[Y])
	{
		map_copy[i++] = v->OBM[v->i++];
	}
	map_copy[i] = '\0';
	return (map_copy);
}

void	map_toscreen(t_vis *v)
{
	int		i;
	char 	*map_cpy;

	i = 0;
	map_cpy = copy_map(v);
	v->img = mlx_new_image(v->mlx, v->size[X] * v->width + 1, v->size[Y] * v->height + 1);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
	build_borders(v);
	while (i < v->size[X] * v->size[Y])
	{
		if (map_cpy[i] == 'O' || map_cpy[i] == 'o')
			put_to_image(v, i % v->size[X], i / v->size[X], 0x56f442);
		else if (map_cpy[i] == 'X' || map_cpy[i] == 'x')
			put_to_image(v, i % v->size[X], i / v->size[X], 0xef8d8d);
		else	
			put_to_image(v, i % v->size[X], i / v->size[X], 0x2F4F4F);
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img,
	(800 - v->width * v->size[X]) / 2, (1000 - v->height * v->size[Y]) / 2);
	free(map_cpy);
	free(v->img);
	free(v->data);
}

void	quit(t_vis *v)
{
	free(v->OBM);
	free(v->img);
	free(v->data);
	free(v->win);
	free(v->mlx);
	exit(1);
}

int		deal_key(int key, t_vis *v)
{
	if (key == 53)
		quit(v);
	if (key == 124 && !(v->OBM[v->i]))
		return (key);
	if (key == 126)
		v->i = (v->count - 2) * v->size[X] * v->size[Y];
	if (key == 125)
		v->i = 0;
	if (key == 123)
	{
		if (v->i - (v->size[X] * v->size[Y] * 2) <= 0)
			return (key);
		v->i -= v->size[X] * v->size[Y] * 2;
	}
	if (key == 126 || key == 124 || key == 125 || key == 123)
	{
		mlx_destroy_image(v->mlx, v->img);
		map_toscreen(v);
	}
	return (key);
}

void	visualiser(t_vis *v)
{
	v->width = 10;
	v->height = 15;
	if (v->size[X] > 40)
		v->width = 4;
	if (v->size[Y] > 40)
		v->height = 6;
	v->i = 0;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 800, 1000, "FILLER");
	//draw_banner(v);
	map_toscreen(v);
	mlx_hook(v->win, 2, 0, deal_key, v);
	mlx_loop(v->mlx);
	mlx_loop_hook(v->mlx, deal_key, v);
}
