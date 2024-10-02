# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 12:29:48 by amousaid          #+#    #+#              #
#    Updated: 2024/10/02 17:59:29 by amousaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -rf
MLX_PATH = ./minilibx
MLX_NAME = ./minilibx/libmlx.a
MLX_CMD = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

LIBFT = ./libft/libft.a
CUB3D_SRC = main.c ./utils/get_next_line.c ./utils/get_next_line_utils.c\
			checks/check_map_file.c
OBJ = $(CUB3D_SRC:.c=.o)

all: $(NAME)
bonus: $(BONUS)

$(LIBFT):
		$(MAKE) --no-print-directory -C ./libft

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_CMD) -o $(NAME)
		@echo "✅-------✅IS MAKE✅-------✅"

$(BONUS): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_CMD) -o $(BONUS)
		@echo "✅-------✅BONUS IS MAKE✅-------✅"

clean:
	$(MAKE) clean --no-print-directory -C ./libft
	$(RM) $(OBJ)
	@echo "🧹--------🧹IS CLEAN🧹--------🧹"

fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libft
	$(RM) $(NAME)
	@echo "🧹-----🧹IS FULL CLEAN🧹-----🧹"

re: fclean all

.SILENT:
