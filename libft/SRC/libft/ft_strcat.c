/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:02:16 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 13:18:49 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}
