#include "filler.h"
#include <stdio.h>

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
		x = i + (j % fill->p_dim[1]);
		if (i % fill->d[1] + j % fill->p_dim[1] < fill->d[1])
		{
		if (piece[j] == '*' && (map[x] == fill->smother || map[x] == fill->smother + 32))
			count++;
		if (piece[j] == '*' && (map[x] == fill->opp || map[x] == fill->opp + 32))
			return (0);
		}
		if (piece[j] == '*' && map[x] == '\0')
			return (-1);
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

void	put_coords(int c1, int c2)
{
	ft_putnbr(c2);
	ft_putchar(' ');
	ft_putnbr(c1);
	ft_putchar('\n');
}
/*
void	get_contact(t_fill *fill, char *map, char *piece, int i)
{
	int	j;
	int	x;

	j = 0;
	while (piece[j])
	{
		x = i + (j % fill->p_dim[1]);
	}
}*/

void	get_xmax(char *piece, t_fill *fill)
{
	int	i;

	i = 0;
	fill->px_max = 0;
	while (piece[i])
	{
		if (piece[i] == '*')
			fill->px_max = (i % fill->p_dim[1] > fill->px_max) ? i % fill->p_dim[1] : fill->px_max;
		i++;
	}

}

void	filler(char **line, char *map, t_fill *fill)
{
	int		i;
	int		ret;
	char	*piece;

	i = 0;
	piece = build_piece(line, fill->p_dim);
	get_xmax(piece, fill);
	fill->distance_opp = 100000;
	while (map[i + fill->px_max])
	{
		if (i % fill->d[1] + fill->px_max == fill->d[1])
			i += fill->px_max;
		if ((ret = can_put(map, fill, piece, i)) == 1)
		{
			//get_contact(fill, map, piece, i);
			get_distance(fill, piece, i);
		}
		if (ret == -1)
			break ;
		i++;
	}
	free(piece);
	put_coords(fill->seek_put % fill->d[1], fill->seek_put / fill->d[1]);
}
