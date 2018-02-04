
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:59:23 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 13:28:07 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <pthread.h>

pthread_t fast;

	i->img = mlx_new_image(i->mlx, i->isize, i->isize);
	i->data = mlx_get_data_addr(i->img, &(i->bpp), &(i->sl), &(i->endian));
	get_dimensions(i);
	pthread_create(&fast, NULL, thread_second, i);
	thread_first(i);
	pthread_join(fast, NULL);
	mlx_put_image_to_window(i->mlx, i->win, i->img, 0, 0);
	add_mapkey(i);

char	*ft_lsttstr_del(t_list **list)
{
	t_list		*tmp;
	int			count;
	char		*dst;
	p_thread	fast;

	count = 0;
	tmp = *list;
	while (tmp != NULL)
	{
		count += tmp->content_size;
		tmp = tmp->next;
	}
	thread_first(count / 2, &list, )
	if (!(dst = (char *)ft_memalloc(count + 1)))
		return (NULL);
	dst[0] = '\0';
	count = 0;
	while (*list != NULL)
	{
		tmp = *list;
		ft_strcat_i(dst, tmp->content, count);
		count += tmp->content_size;
		free(tmp->content);
		*list = (*list)->next;
		free(tmp);
	}
	dst[count] = '\0';
	return (dst);
}
