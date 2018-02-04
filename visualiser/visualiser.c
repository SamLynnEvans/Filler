/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:31:57 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 12:42:07 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	put_to_image(t_vis *v, int x, int y, int color)
{
	int	pos;
	int	i;
	int	j;
	int	tmp;
	
	j = 0;
	pos = (x * 4 * v->width) + (y * v->sl * v->height);
	while (j++ < v->height - 1)
	{
		tmp = pos;
		i = 0;
		while (i++ < v->width)
		{
			v->data[tmp++] = color;
			v->data[tmp++] = color >> 8;
			v->data[tmp++] = color >> 16;
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
	v->img = mlx_new_image(v->mlx, v->size[X] * v->width, v->size[Y] * v->height);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
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
	mlx_put_image_to_window(v->mlx, v->win, v->img, (800 - v->width * v->size[X]) / 2, (1000 - v->height * v->size[Y]) / 2);
	free(map_cpy);
	free(v->img);
	free(v->data);
}



int		deal_key(int key, t_vis *v)
{
	if (key == 53)
		exit(1);
	if (key == 124)
	{
		if (!(v->OBM[v->i]))
		{
		//	special_print(v);
			return (key);
		}
		mlx_clear_window(v->mlx, v->win);
		map_toscreen(v);
	}
	if (key == 123)
	{
		if (v->i - (v->size[X] * v->size[Y] * 2) <= 0)
			return (key);
		v->i -= v->size[X] * v->size[Y] * 2;
		mlx_clear_window(v->mlx, v->win);
		map_toscreen(v);
	}
	return (key);
}

void	visualiser(t_vis *v)
{
//	if (v->size[X] <= 20)
	v->width = 10;
//	if (v->size[Y] <= 20)
	v->height = 15;
//	if (v->size[X] < 40 && v->size[X] > 20)
//	v->width = 12;
//	if (v->size[Y] < 40 && v->size[Y] > 20)
//	v->height = 18;
	if (v->size[X] > 40)
		v->width = 4;
	if (v->size[Y] > 40)
		v->height = 6;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 800, 1000, "FILLER");
	map_toscreen(v);
	mlx_hook(v->win, 2, 0, deal_key, v);
//	print_map(v);
	mlx_loop(v->mlx);
	mlx_loop_hook(v->mlx, deal_key, v);
}
