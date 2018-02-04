/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:52:21 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 12:49:18 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H
# define X 1
# define Y 0

# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"


typedef struct	s_vis
{
	char	*line;
	char	*OBM;
	char	**maps;
	int		count;
	char	*data;
	int		bpp;
	int		endian;
	int		first;
	int		sl;
	int		i;
	char	*img;
	void	*win;
	void	*mlx;
	char	*map;
	int		size[2];
	int		width;
	int		height;
}				t_vis;

void	visualiser(t_vis *v);

#endif
