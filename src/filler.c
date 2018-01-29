#include "filler.h"
#include <stdio.h>

void	put_coords(int c1, int c2)
{
	ft_putnbr(c2);
	ft_putchar(' ');
	ft_putnbr(c1);
	ft_putchar('\n');
}

char	*build_piece(char **line, int *coord)
{
	get_next_line(0, line);
	get_dimensions(coord, *line);
	free(*line);
	return (get_map(line, coord, 0));
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

float	distance_from_opp(int coord, t_fill *fill)
{
	int height;
	int	width;
	float	i;
	float total;

	i = 0;
	height = fill->opp_centre / fill->d[1] - coord / fill->d[1];
	width = fill->opp_centre % fill->d[1] - coord % fill->d[1];
	total = (float)(width * width + height * height);
	while(i * i <= total)
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
			if ((distance = distance_from_opp(coord, fill)) < fill->distance_opp)
			{
				fill->distance_opp = distance;
				fill->seek_put = i;
			}
		}
		j++;
	}

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
			if (x > 0 && (map[x - 1] == fill->opp || map[x - 1] == fill->opp + 32))
				count++;
			else if (x > fill->d[1] && 
			(map[x - fill->d[1]] == fill->opp || map[x - fill->d[1]] == fill->opp + 32))
				count++;
			else if (x + fill->d[1] < fill->d[1] * fill->d[0] &&
			(map[x + fill->d[1]] == fill->opp || map[x + fill->d[1]] == fill->opp + 32))
				count++;
			else if (((x + 1) % fill->d[1]) && 
			(map[x + 1] == fill->opp || map[x + 1] == fill->opp + 32))
				count++;
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

void	filler(char **line, char *map, t_fill *fill)
{
	int		i;
	int		ret;
	char	*piece;
	int		first;

	first = 0;
	i = 0;
	piece = build_piece(line, fill->p_dim);
	get_xymax(piece, fill);
	fill->distance_opp = 100000;
	fill->contact = 0;
	while (fill->d[0] > i / fill->d[1] + fill->py_max)
	{
		if (i % fill->d[1] + fill->px_max == fill->d[1])
		{
			i += fill->px_max;
			continue ;
		}
		if ((ret = can_put(map, fill, piece, i)) == 1)
		{
			first++;
		//	{
				//can_putdebug(map, fill, piece, i);
			//	fill->seek_put = i;
		//	}
			get_contact(fill, map, piece, i);
			get_distance(fill, piece, i);
		}
		i++;
	}
	free(piece);
	if (!first)
		put_coords(0, 0);
	else if (fill->contact)
		put_coords(fill->contact_put % fill->d[1], fill->contact_put / fill->d[1]);
	else
		put_coords(fill->seek_put % fill->d[1], fill->seek_put / fill->d[1]);
}
