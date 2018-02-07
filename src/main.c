/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:24:31 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/06 17:20:10 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	*get_map(char **line, int d[2], int mod)
{
	char	*map;
	int		i;
	int		ret;

	i = 0;
	if (!(map = malloc(sizeof(char) * d[0] * d[1] + 1)))
		return (NULL);
	while (i < d[0] * d[1] && (ret = get_next_line(0, line)) > 0)
	{
		if ((int)ft_strlen(*line) - mod != d[1])
			return (NULL);
		map[i] = line[0][i % d[1] + mod];
		while (++i % d[1])
		{
			if ((int)ft_strlen(*line) - mod != d[1])
				return (NULL);
			map[i] = line[0][i % d[1] + mod];
		}
		free(*line);
	}
	if (i != d[0] * d[1])
		return (NULL);
	map[i] = '\0';
	return ((ret == -1) ? NULL : map);
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

int		get_info(char **line, t_fill *fill)
{
	int	i;
	int	ret;

	i = 0;
	while ((ret = get_next_line(0, line)) == 1)
	{
		while (i < 10)
			if (!(line[0][i++]))
				return (-1);
		if (i++ == 10 && ft_strncmp("$$$ exec p", *line, 10) != 0)
			return (-1);
		if (line[0][0] == '$')
		{
			fill->smother = (line[0][10] == '1') ? 'O' : 'X';
			fill->opp = (fill->smother == 'O') ? 'X' : 'O';
		}
		if (!(ft_strncmp(*line, "Pl", 2)))
		{
			get_dimensions(fill->d, *line);
			free(*line);
			break ;
		}
		free(*line);
	}
	return (ret);
}

int		main(void)
{
	char	*line;
	t_fill	fill;
	char	*map;
	int		first;

	first = 0;
	if (get_info(&line, &fill) != 1)
		return (0);
	while (get_next_line(0, &line) > 0)
	{
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
