#include "filler.h"
#include <stdio.h>

char *get_map(char **line, int d[2], int mod)
{
	char	*map;
	int		i;

	i = 0;
	if (!(map = malloc(sizeof(char) * d[0] * d[1] + 1)))
		return (NULL);
	while (i < d[0] * d[1]  && get_next_line(0, line) > 0)
	{
		map[i] = line[0][i % d[1] + mod];
		while (++i % d[1])
			map[i] = line[0][i % d[1] + mod];
		free(*line);
	}
	map[i] = '\0';
	return (map);
}

void	get_oppcentre(char *map, t_fill *fill)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == fill->opp)
		{
			fill->opp_centre = i;
			return ;
		}
		i++;
	}
} 

void	get_dimensions(int *dimensions, char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (ft_isdigit(*line))
		{
			dimensions[i++] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
		}
		line++;
	}
}

int main()
{
	char	*line;
	t_fill	fill;
	char	*map;
	int		first;

	first = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '$')
		{
			fill.smother = (line[10] == '1') ? 'O' : 'X';
			fill.opp = (fill.smother == 'O') ? 'X' : 'O';
		}
		if (!(ft_strncmp(line, "Pl", 2)))
			get_dimensions(fill.d, line);
		if (line[0] == ' ')
		{	
			if (!(map = get_map(&line, fill.d, 4)))
				return (0);
			if (!(first++))
				get_oppcentre(map, &fill);
			filler(&line, map, &fill);
			free(map);
		}
		else
			free(line);
	}
}
