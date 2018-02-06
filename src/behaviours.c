/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviours.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:20:27 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/06 13:30:02 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_coords(int c1, int c2, t_fill *fill)
{
	c1 -= fill->px_min;
	c2 -= fill->py_min;
	ft_putnbr(c2);
	ft_putchar(' ');
	ft_putnbr(c1);
	ft_putchar('\n');
}

int		contact_count(char *map, t_fill *fill, int x)
{
	if (x > 0 && (map[x - 1] == fill->opp || map[x - 1] == fill->opp + 32))
		return (1);
	if (x > fill->d[1] &&
	(map[x - fill->d[1]] == fill->opp || map[x - fill->d[1]] == fill->opp + 32))
		return (1);
	if (x + fill->d[1] < fill->d[1] * fill->d[0] &&
	(map[x + fill->d[1]] == fill->opp || map[x + fill->d[1]] == fill->opp + 32))
		return (1);
	if (((x + 1) % fill->d[1]) &&
	(map[x + 1] == fill->opp || map[x + 1] == fill->opp + 32))
		return (1);
	return (0);
}

void	get_contact(t_fill *fill, char *map, char *piece, int i)
{
	int	j;
	int	x;
	int count;
	int	orig;

	orig = i;
	count = 0;
	j = 0;
	while (piece[j])
	{
		if (piece[j] == '*')
		{
			x = i + (j % fill->p_dim[1]);
			count += contact_count(map, fill, x);
		}
		j++;
		if (!(j % fill->p_dim[1]))
			i += fill->d[1];
	}
	if (count > fill->contact)
	{
		fill->contact = count;
		fill->contact_put = orig;
	}
}

float	distance_from_opp(int coord, t_fill *fill)
{
	int		height;
	int		width;
	float	i;
	float	total;

	i = 0;
	height = fill->opp_centre / fill->d[1] - coord / fill->d[1];
	width = fill->opp_centre % fill->d[1] - coord % fill->d[1];
	total = (float)(width * width + height * height);
	while (i * i <= total)
	{
		if (i * i == total)
			return (i);
		i += 0.1;
	}
	return (i);
}

void	get_distance(t_fill *fill, char *piece, int i)
{
	int		j;
	float	distance;
	int		coord;

	j = 0;
	while (piece[j])
	{
		if (piece[j] == '*')
		{
			coord = i + (j / fill->p_dim[1]) * fill->d[1] + j % fill->p_dim[1];
			if ((distance = distance_from_opp(coord, fill))
			< fill->distance_opp)
			{
				fill->distance_opp = distance;
				fill->seek_put = i;
			}
		}
		j++;
	}
}
