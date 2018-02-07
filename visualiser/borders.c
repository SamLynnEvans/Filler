/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:37:34 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/06 17:19:53 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

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
			mlx_string_put(v->mlx, v->win, 300, 920, 0xFFFFFF,
	"PLAYER ONE WINS !!!!");
	}
}

void	check(t_vis *v)
{
	char *line;

	if (get_next_line(0, &line) != 1)
		exit(1);
	if (ft_strncmp(line, "# --------------", 16) != 0)
		exit(1);
	ft_putstr("loading game... (big maps take longer...)\n");
	get_size(line, v);
}

void	quit(t_vis *v)
{
	free(v->obm);
	free(v->win);
	free(v->mlx);
	exit(1);
}

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
			tmp = x * 4 + y * v->sl;
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
