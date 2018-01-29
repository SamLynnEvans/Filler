#ifndef FILLER_H
#define FILLER_H

# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_fill
{
	char	smother;
	char	opp;
	int		d[2];
	int		p_dim[2];
	int		opp_centre;
	int		seek_put;
	float	distance_opp;
	int		contact;
	int		px_max;
}				t_fill;

void	filler(char **line, char *map, t_fill *fill);
char	*build_piece(char **line, int *coord);
void	get_dimensions(int *dimensions, char *line);
char 	*get_map(char **line, int d[2], int mod);
void	print_map(char *map, int end_line);

#endif
