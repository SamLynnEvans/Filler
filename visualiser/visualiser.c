/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:31:57 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 20:13:10 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	build_borders(t_vis *v)
{
	int	x;
	int	y;
	int	tmp;
	int h;
	int	w;

	h = (1000 - v->height * v->size[Y]) / 2 - 1;
	w = (800 - v->width * v->size[X]) / 2 - 1;
	y = h;
	while (y < v->size[Y] * v->height + h + 1)
	{
		x = w;
		while (x < v->width * v->size[X] + w + 1)
		{
			tmp = x * 4 + y * v->sl;;
			v->data[tmp++] = 0xBD; 
			v->data[tmp++] = 0xBD; 
			v->data[tmp++] = 0xBD;
			x++;
		}
		y++;
	}
}

void	draw_banner(t_vis *v)
{
	int	x;
	int	y;
	int	tmp;

	y = 0;
	while (y < 150)
	{
		x = 0;
		while (x < 800)
		{
			tmp = x * 4 + y * v->sl;
			v->data[tmp++] = 0x19; 
			v->data[tmp++] = 0x03; 
			v->data[tmp++] = 0x56;
			tmp = x * 4 + (850 + y) * v->sl;
			v->data[tmp++] = 0x19; 
			v->data[tmp++] = 0x03; 
			v->data[tmp++] = 0x56;
			x++;
		}
		y++;
	}
}

void	put_to_image(t_vis *v, int x, int y, int color)
{
	int	pos;
	int	i;
	int	j;
	int	tmp;
	int h[2];

	h[0] = (1000 - v->height * v->size[Y]) / 2;
	h[1] = (800 - v->width * v->size[X]) / 2;
	j = 0;
	pos = (x * 4 * v->width) + (y * v->sl * v->height) + 4 * h[1] + v->sl * h[0];
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

void	print_strings(t_vis *v)
{
	mlx_string_put(v->mlx, v->win, 320, 70, 0xFFFFFF,
	"SUPER FILLER 2000");
	if (v->score_print)
	{
		if (v->score[1] > v->score[0])
			mlx_string_put(v->mlx, v->win, 310, 880, 0xFFFFFF,
	"PLAYER TWO WINS !!!!");
		else
			mlx_string_put(v->mlx, v->win, 300, 940, 0xFFFFFF,
	"PLAYER ONE WINS !!!!");
	}
}
void	map_toscreen(t_vis *v)
{
	int		i;
	char 	*map_cpy;

	i = 0;
	map_cpy = copy_map(v);
	v->img = mlx_new_image(v->mlx, 800, 1000);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
	draw_banner(v);
	build_borders(v);
	while (i < v->size[X] * v->size[Y])
	{
		if (map_cpy[i] == 'O' || map_cpy[i] == 'o')
			put_to_image(v, i % v->size[X], i / v->size[X], 0x4682B4);
		else if (map_cpy[i] == 'X' || map_cpy[i] == 'x')
			put_to_image(v, i % v->size[X], i / v->size[X], 0x4B0082);
		else	
			put_to_image(v, i % v->size[X], i / v->size[X], 0x2F4F4F);
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	print_strings(v);
	free(map_cpy);
	free(v->img);
	free(v->data);
}

void	quit(t_vis *v)
{
	free(v->OBM);
	free(v->win);
	free(v->mlx);
	exit(1);
}

int		deal_key(int key, t_vis *v)
{
	if (key == 53)
		quit(v);
	if ((key == 124 && !(v->OBM[v->i])) || key == 126)
		v->score_print = 1;
	if (key == 124 && !(v->OBM[v->i]))
		v->i -= v->size[X] * v->size[Y];
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
		mlx_clear_window(v->mlx, v->win);
		map_toscreen(v);
	}
	return (key);
}

void	visualiser(t_vis *v)
{
	v->width = 10;
	v->height = 15;
	v->score_print = 0;
	if (v->size[X] > 40)
		v->width = 4;
	if (v->size[Y] > 40)
		v->height = 6;
	v->i = 0;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 800, 1000, "FILLER");
	map_toscreen(v);
	mlx_hook(v->win, 2, 0, deal_key, v);
	mlx_loop(v->mlx);
	mlx_loop_hook(v->mlx, deal_key, v);
}
