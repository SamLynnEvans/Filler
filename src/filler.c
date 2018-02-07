/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:24:55 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/07 09:13:41 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
}

char	*trim_piece(char **piece, t_fill *fill)
{
	int		i;
	char	*trim;
	int		j;

	j = 0;
	trim = malloc(sizeof(char) * (fill->py_max - fill->py_min + 1)
	* (fill->px_max - fill->px_min + 1) + 1);
	i = fill->py_min * fill->p_dim[1];
	while (i < (fill->py_max + 1) * fill->p_dim[1])
	{
		if ((i % fill->p_dim[1] < fill->px_min)
		|| (i % fill->p_dim[1]) > fill->px_max)
			i++;
		else
			trim[j++] = piece[0][i++];
	}
	trim[j] = '\0';
	free(*piece);
	return (trim);
}

char	*build_piece(char **line, t_fill *fill)
{
	char *piece;

	fill->distance_opp = 100000;
	fill->contact = 0;
	get_next_line(0, line);
	get_dimensions(fill->p_dim, *line);
	free(*line);
	piece = get_map(line, fill->p_dim, 0);
	get_xymax(piece, fill);
	piece = trim_piece(&piece, fill);
	fill->p_dim[1] = fill->px_max - fill->px_min + 1;
	fill->p_dim[0] = fill->py_max - fill->py_min + 1;
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
		if (piece[j] == '*' &&
		((i % fill->d[1] + j % fill->p_dim[1]) >= fill->d[1]))
			return (0);
		else if (piece[j] == '*')
		{
			x = i + (j % fill->p_dim[1]);
			if (map[x] == fill->smother || map[x] == fill->smother + 32)
				count++;
			if (map[x] == fill->opp || map[x] == fill->opp + 32 || count > 1)
				return (0);
		}
		j++;
		if (!(j % fill->p_dim[1]))
			i += fill->d[1];
	}
	return (1);
}

void	filler(char **line, char *map, t_fill *f)
{
	int		i;
	int		ret;
	char	*piece;

	i = 0;
	piece = build_piece(line, f);
	while (f->d[0] >= i / f->d[1] + f->p_dim[0])
	{
		if (i % f->d[1] + f->p_dim[1] > f->d[1])
		{
			i += f->p_dim[1];
			continue ;
		}
		if ((ret = can_put(map, f, piece, i)) == 1)
		{
			get_contact(f, map, piece, i);
			get_distance(f, piece, i);
		}
		i++;
	}
	if (f->contact)
		put_coords(f->contact_put % f->d[1], f->contact_put / f->d[1], f);
	else
		put_coords(f->seek_put % f->d[1], f->seek_put / f->d[1], f);
	free(piece);
}
