/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:53:03 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 22:04:46 by slynn-ev         ###   ########.fr       */
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

void	*thread_second(void *l)
{
	t_list	*lst;
	int		len;
	int		half;
	char 	*dst;
	int		count;

	count = 0;
	lst = (t_list *)l;
	half = lst->nodes / 2;
	len = half * lst->content_size;
	dst = malloc(len + 1);
	len = 0;
	while (len++ < half )
	{
		ft_strcat_i(dst, lst->content, count);
		count += lst->content_size;
		lst = lst->next;
	}
	dst[count] = '\0';
	return ((void *)dst);
}


void	build_one_big_map(t_vis *v, t_list *lst)
{
	pthread_t	fast;
	int			half;
	int			i;
	char		*tmp;

	i = 0;
	lst->nodes = v->count;
	half = v->count / 2;
	pthread_create(&fast, NULL, thread_second, lst);
	tmp = malloc((lst->nodes - half) * lst->content_size + 1);
	while (i++ < half)
		lst = lst->next;
	lst = lst->next;
	i = 0;
	while (lst != NULL)
	{
		ft_strcat_i(tmp, lst->content, i);
		i += lst->content_size;
		lst = lst->next;
	}
	pthread_join(fast, (void *)&(v->OBM));
	v->OBM = ft_strjoin_free(v->OBM, tmp);
	free(tmp);
}

int main()
{
	int		i;
	t_vis	v;
	t_list	*tmp;
	t_list	*lst;

	i = 0;
	v.count = 0;
	lst = NULL;
	get_size(v.line, &v);
	ft_putstr("loading game... (big maps take longer...)\n");
	while (get_next_line(0, &(v.line)) > 0)
	{
		if (ft_strncmp("==", v.line, 2) == 0)
			v.score[i++] = ft_atoi(v.line + 10);
		if (ft_strncmp("   ", v.line, 2) == 0)
		{
			tmp = ft_lstnew_ptr((void *)(get_map(&(v.line), v.size, 4)), v.size[X] * v.size[Y]);
			ft_lstaddend(&lst, tmp);
			v.count++;
		}
		else
			free(v.line);
	}
	visualiser(&v, lst);
}
