/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:52:21 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 22:04:29 by slynn-ev         ###   ########.fr       */
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
# include <pthread.h>

typedef struct	s_vis
{
	int		score[2];
	int		score_print;
	char	*line;
	char	*OBM;
	char	**maps;
	int		count;
	char	*data;
	char	*data2;
	int		bpp;
	int		bpp2;
	int		endian;
	int		endian2;
	int		sl;
	int		sl2;
	int		i;
	char	*img;
	char	*img2;
	void	*win;
	void	*mlx;
	char	*map;
	int		size[2];
	int		width;
	int		height;
}				t_vis;

void	visualiser(t_vis *v, t_list *lst);
void	build_one_big_map(t_vis *v, t_list *lst);

#endif
