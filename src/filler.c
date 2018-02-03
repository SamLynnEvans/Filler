/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:24:55 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 13:47:12 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_coords(int c1, int c2)
{
	ft_putnbr(c2);
	ft_putchar(' ');
	ft_putnbr(c1);
	ft_putchar('\n');
}

void	get_xymax(char *piece, t_fill *fill)
{
	int	i;

	i = 0;
	fill->px_max = 0;
	fill->py_max = 0;
	fill->px_min = fill->p_dim[1];
	fill->py_min = fill->p_dim[0];
	while (piece[i])
	{
		if (piece[i] == '*')
		{
			fill->px_max = (i % fill->p_dim[1] > fill->px_max) ?
			i % fill->p_dim[1] : fill->px_max;
			fill->py_max = (i / fill->p_dim[1] > fill->py_max) ?
			i / fill->p_dim[1] : fill->py_max;
			fill->px_min = (i % fill->p_dim[1] < fill->px_min) ?
			i % fill->p_dim[1] : fill->px_min;
			fill->py_min = (i / fill->p_dim[1] < fill->py_min) ?
			i / fill->p_dim[1] : fill->py_min;
		}
		i++;
	}
	ft_intdebug(fill->py_min, "ymin");
	ft_intdebug(fill->px_min, "xmin");
}

char	*trim_piece(char *piece, t_fill *fill)
{
	int		i;
	char	*trim;
	int		j;


	j = 0;
	trim = malloc(sizeof(char) * (fill->py_max - fill->py_min + 1)
	* (fill->px_max - fill->px_min + 1));
	i = fill->py_min * fill->p_dim[1];
	ft_intdebug(i, "i_strt");
	ft_intdebug(fill->py_max, "pymac");
	while (i < (fill->py_max + 1) * fill->p_dim[1])
	{
		if ((i % fill->p_dim[1] < fill->px_min) || (i % fill->p_dim[1]) > fill->px_max)
			i++;
		else
			trim[j++] = piece[i++];
	}
	trim[j] = '\0';
	return (trim);
}

char	*build_piece(char **line, t_fill *fill)
{
	char *piece;
	char *exp;

	fill->distance_opp = 100000;
	fill->contact = 0;
	get_next_line(0, line);
	get_dimensions(fill->p_dim, *line);
	free(*line);
	piece = get_map(line, fill->p_dim, 0);
	get_xymax(piece, fill);
	exp = trim_piece(piece, fill);
	ft_putstr(exp);
	return (piece);
}

int		can_put(char *map, t_fill *fill, char *piece, int i)
{
	int	j;
	int	count;
	int	x;

	count = 0;
	j = 0;
	while (piece[j])
	{
		if (piece[j] == '*' && ((i % fill->d[1] + j % fill->p_dim[1]) < fill->d[1]))
		{
			x = i + (j % fill->p_dim[1]);
			if (map[x] == fill->smother || map[x] == fill->smother + 32)
				count++;
			if (map[x] == fill->opp || map[x] == fill->opp + 32)
				return (0);
		}
		j++;
		if (!(j % fill->p_dim[1]))
			i += fill->d[1];
	}
	return (count == 1) ? 1 : 0;
}

void	filler(char **line, char *map, t_fill *fill)
{
	int		i;
	int		ret;
	char	*piece;
	
	i = 0;
	piece = build_piece(line, fill);
	while (fill->d[0] > i / fill->d[1] + fill->py_max)
	{
		if (i % fill->d[1] + fill->px_max == fill->d[1])
		{
			i += fill->px_max;
			continue ;
		}
		if ((ret = can_put(map, fill, piece, i)) == 1)
		{
			get_contact(fill, map, piece, i);
			get_distance(fill, piece, i);
		}
		i++;
	}
	if (fill->contact)
		put_coords(fill->contact_put % fill->d[1], fill->contact_put / fill->d[1]);
	else
		put_coords(fill->seek_put % fill->d[1], fill->seek_put / fill->d[1]);
	free(piece);
}
