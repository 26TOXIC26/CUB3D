.PHONY: all re clean fclean bonus

# Program file name
NAME	= cub3D

# Colors
GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0m

# Mode
BONUS = 0

# Compiler and compilation flags
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -g3 -fsanitize=address

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH = ./sources/
SRC		= 	main.c \
			error.c \
			init/init_data.c \
			init/init_mlx.c \
			init/init_textures.c \
			parsing/check_args.c \
			parsing/parse_data.c \
			parsing/get_file_data.c \
			parsing/create_game_map.c \
			parsing/check_textures.c \
			parsing/check_map.c \
			parsing/check_map_borders.c \
			parsing/fill_color_textures.c \
			parsing/parsing_utils.c \
			movement/input_handler.c \
			movement/player_dir.c \
			movement/player_pos.c \
			movement/player_move.c \
			movement/player_rotate.c \
			render/raycasting.c \
			render/render.c \
			render/texture.c \
			render/image_utils.c \
			render/minimap_render.c \
			render/minimap_image.c \
			exit/exit.c \
			exit/free_data.c \
			debug/debug.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/init
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/movement
	mkdir -p $(OBJ_PATH)/render
	mkdir -p $(OBJ_PATH)/debug
	mkdir -p $(OBJ_PATH)/exit

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "$(GREEN)=========================$(NC)"
	@echo "$(GREEN)      Cub3D Created      $(NC)"
	@echo "$(GREEN)=========================$(NC)"

# Libft rule
$(LIBFT):
	make --no-print-directory -sC  $(LIBFT_PATH)

# MLX rule
$(MLX):
	make -sC $(MLX_PATH)

bonus: fclean
	make --no-print-directory BONUS=1 all

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	@echo "$(RED)=========================$(NC)"
	@echo "$(RED)      Objects removed    $(NC)"
	@echo "$(RED)=========================$(NC)"

# Remove program executable
fclean: clean
	rm -f $(NAME)
	@echo "$(RED)=========================$(NC)"
	@echo "$(RED)      Cub3D removed      $(NC)"
	@echo "$(RED)=========================$(NC)"

# Clean + remove executable
re: fclean all

.SILENT:
