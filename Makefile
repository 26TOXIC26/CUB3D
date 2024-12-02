# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 12:29:48 by amousaid          #+#    #+#              #
#    Updated: 2024/12/02 07:04:11 by ebouboul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
RM = rm -rf
MLX_PATH = ./minilibx
MLX_NAME = ./minilibx/libmlx.a
MLX_CMD = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

CUB3D_SRC = main.c\
			 ./utils/get_next_line.c\
			 ./utils/utils.c ./utils/ft_atoi.c ./utils/ft_isdigit.c\
			 ./utils/ft_strncmp.c ./utils/ft_strcmp.c ./utils/ft_strchr.c ./utils/ft_strlen.c\
			 ./utils/ft_strjoin.c ./utils/ft_strdup.c ./utils/ft_putchar_fd.c\
			 ./utils/ft_putstr_fd.c ./utils/ft_split.c ./utils/ft_substr.c\
			 ./utils/ft_calloc.c checks/check_map_file.c checks/check_map_file2.c\
			 ./utils/ft_memset.c utils/free_mlx.c\
			 ./src/init_data.c\
			 ./src/init/init_data.c\
			./src/init/init_mlx.c\
			./src/init/init_textures.c\
			./src/movement/input_handler.c\
			./src/movement/player_dir.c\
			./src/movement/player_move.c\
			./src/movement/player_pos.c\
			./src/movement/player_rotate.c\
			./src/render/image_utils.c\
			./src/render/minimap_image.c\
			./src/render/minimap_render.c\
			./src/render/raycasting.c\
			./src/render/render.c\
			./src/render/texture.c\
			
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(CUB3D_SRC:.c=.o))

all: $(NAME)
bonus: $(BONUS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(MLX_CMD) -o $(NAME)
		@echo "✅-------✅IS MAKE✅-------✅"

$(BONUS): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(MLX_CMD) -o $(BONUS)
		@echo "✅-------✅BONUS IS MAKE✅-------✅"

clean:
	$(RM) $(OBJ_DIR)
	@echo "🧹--------🧹IS CLEAN🧹--------🧹"

fclean: clean
	$(RM) $(NAME)
	@echo "🧹-----🧹IS FULL CLEAN🧹-----🧹"

re: fclean all

.SILENT:
