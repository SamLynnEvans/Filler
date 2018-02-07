SRC_NAME = main.c \
filler.c \
behaviours.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = src

OBJ_PATH = obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

NAME = slynn-ev.filler

DEPS = includes/filler.h

FLAGS = -Wall -Wextra -Werror

CPPFLAGS = -Iincludes \
-Ilibft/Includes \

LIB = libft

LIB_A = libftprintf.a \

all: library $(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB)/$(LIB_A) -g

library:
	@make -C $(LIB)
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(OBJ_PATH)
	gcc $(FLAGS) -o $@ -c $< $(CPPFLAGS)

clean:
	make clean -C $(LIB)
	rm -fr $(OBJ_PATH)

fclean : clean
	rm -f $(LIB)/$(LIB_A)
	rm -f $(NAME)

re : fclean all
