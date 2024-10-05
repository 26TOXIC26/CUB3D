# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 12:29:48 by amousaid          #+#    #+#              #
#    Updated: 2024/10/05 10:34:19 by amousaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
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
			 ./utils/ft_calloc.c checks/check_map_file.c checks/check_map_file2.c
OBJ = $(CUB3D_SRC:.c=.o)

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(MLX_CMD) -o $(NAME)
		@echo "✅-------✅IS MAKE✅-------✅"

$(BONUS): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(MLX_CMD) -o $(BONUS)
		@echo "✅-------✅BONUS IS MAKE✅-------✅"

clean:
	$(RM) $(OBJ)
	@echo "🧹--------🧹IS CLEAN🧹--------🧹"

fclean: clean
	$(RM) $(NAME)
	@echo "🧹-----🧹IS FULL CLEAN🧹-----🧹"

re: fclean all

.SILENT:
