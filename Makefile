NAME = minirt
INCLUDES = minirt.h
SRC = minirt.c figures_draw.c figures_init.c hook_control.c
OBJ = $(SRC:.c=.o)
REM = rm -rf
MLX = mlx/libmlx.a

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(INCLUDES) $(OBJ) $(SRC) Makefile
	gcc -I $(INCLUDES) $(OBJ) $(MLX) -framework OpenGL -framework AppKit -o $(NAME)

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

clean:
	$(REM) $(OBJ)

fclean:	clean
	$(REM) $(NAME)

re:	fclean all
