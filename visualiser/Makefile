# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/03 17:56:31 by slynn-ev          #+#    #+#              #
#    Updated: 2018/02/06 14:50:49 by slynn-ev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c visualiser.c borders.c

DEPS = includes/vis.h \

INCLUDES = -Iincludes/ \
-I../lib/Includes/ \
-Iminilibx/ \

OBJ = $(SRC:.c=.o)

NAME = vis

FLAGS = -Wall -Wextra -Werror -g

LIBX = minilibx

LIBX_A = libmlx.a

LIB = ../lib

LIB_A = libftprintf.a

FRAME = -framework Appkit \
-framework OpenGL \

all: library $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB)/$(LIB_A) $(LIBX)/$(LIBX_A) $(FRAME)

%.o: %.c $(DEPS)
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

library:
	@make -C $(LIB)
	@make -C $(LIBX)

clean:
	rm -f $(OBJ)
	make clean -C $(LIB)
	make clean -C $(LIBX)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean all
