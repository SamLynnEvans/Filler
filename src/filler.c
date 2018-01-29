#include "filler.h"
#include <stdio.h>

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
	while (piece[i])
	{
		if (piece[i] == '*')
		{
			fill->px_max = (i % fill->p_dim[1] > fill->px_max) ?
			i % fill->p_dim[1] : fill->px_max;
			fill->py_max = (i / fill->p_dim[1] > fill->py_max) ?
			i / fill->p_dim[1] : fill->py_max;
		}
		i++;
	}
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
