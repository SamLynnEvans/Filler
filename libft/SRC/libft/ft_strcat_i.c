/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 13:18:40 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 15:58:18 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_i(char *dst, const char *src, int i)
{
	unsigned long	j;

	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}
