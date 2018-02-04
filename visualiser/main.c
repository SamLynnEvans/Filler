/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:53:03 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 12:36:18 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"

void	get_size(char *line, t_vis *v)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (get_next_line(0, &line) > 0)
		if (strncmp("Pl", line, 2) == 0)
			break ;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			v->size[j++] = ft_atoi(line + i);
		while (ft_isdigit(line[i]))
			i++;
		i++;
	}
	free(line);
}
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

void	print_map(char *OBM, int d[2])
{
	int	i;

	i = 0;
	while (OBM[i])
	{
		if (!(i % d[X]))
			ft_putchar('\n');
		ft_putchar(OBM[i++]);
		if (!(i % (d[X] * d[Y])))
			ft_putchar('\n');
	}

}

int main()
{
	t_vis	v;
	char	*tmp;

	v.count = 0;
	get_size(v.line, &v);
	while (get_next_line(0, &(v.line)) > 0)
	{
		if (ft_strncmp("   ", v.line, 2) == 0)
		{
			free(v.line);
			if (!v.count++)
				v.OBM = get_map(&(v.line), v.size, 4);
			else
			{
				tmp = get_map(&(v.line), v.size, 4);
				v.OBM = ft_strjoin_free(v.OBM, tmp);
				free(tmp);
			}
		}
		else if (ft_strncmp("==", v.line, 2) == 0)
		{
			ft_putnbr(ft_atoi(v.line + 10));
			ft_putchar('\n');
			free(v.line);
		}
		else
			free(v.line);
	}
	v.i = 0;
	ft_putnbr(v.count);
	visualiser(&v);
	//print_map(v.OBM, v.size);
}
