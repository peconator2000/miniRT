NAME = miniRT

LIBRARIES = -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -framework OpenGL -framework AppKit
INCLUDES = -I$(HEADER_DIR) -I$(MINILIBX_HEADERS)

# Header files
HEADER_DIR = ./includes/
HEADER_LIST = miniRT.h colors.h
HEADERS = $(shell ls ./includes/*.h)

# MINILIBX
MINILIBX = $(MINILIBX_DIR)libmlx.a
MINILIBX_DIR = ./minilibx_opengl/
MINILIBX_HEADERS = $(MINILIBX_DIR)

# LIBFT
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)

# SOURCES
SOURCES =	$(shell ls sources/*.c) \
			$(shell ls sources/parse/*.c) \
			$(shell ls sources/vector_operations/*.c) \
			$(shell ls sources/control/*.c) \
			$(shell ls sources/coordinates/*.c) \
			$(shell ls sources/draw/*.c) \
			$(shell ls sources/rays/*.c) \
			$(shell ls sources/color/*.c) \
			$(shell ls sources/new_basis/*.c)


# OBJECTS
OBJ_DIR = ./objects/
OBJECTS	= $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

# UTILS
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx
RM = rm -rf

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS) $(OBJ_DIR) Makefile
	@$(CC) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN).$(RESET)"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@$(MAKE) -sC $(MINILIBX_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(RM) $(MINILIBX)
	@echo "$(NAME): $(RED)$(MINILIBX) was deleted$(RESET)"
	@$(RM) $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
