/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_lstcontent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 21:59:32 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 21:59:45 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_content(void *content, size_t content_size)
{
	if (content_size)
		;
	free(content);
}
