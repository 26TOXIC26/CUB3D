# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 03:42:44 by bamssaye          #+#    #+#              #
#    Updated: 2024/12/07 12:52:55 by amousaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FUN = ft_isalpha.c ft_isdigit.c\
	ft_isalnum.c ft_isascii.c\
	ft_isprint.c ft_strlen.c\
	ft_memset.c ft_bzero.c\
	ft_memcpy.c ft_memmove.c\
	ft_strlcpy.c ft_strlcat.c\
	ft_toupper.c ft_tolower.c\
	ft_strchr.c ft_strrchr.c\
	ft_strncmp.c ft_memchr.c\
	ft_memcmp.c ft_strnstr.c\
	ft_atoi.c ft_calloc.c ft_strdup.c\
	ft_substr.c ft_strjoin.c ft_putnbr_fd.c\
	ft_strtrim.c ft_split.c\
	ft_itoa.c ft_strmapi.c\
	ft_striteri.c ft_putchar_fd.c\
	ft_putstr_fd.c ft_putendl_fd.c\
	ft_lstnew.c ft_lstadd_back.c\
	ft_lstlast.c ft_lstsize.c\
	get_next_line.c gnl_utils.c\

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rc
RM = rm -rf
OBG =  $(FUN:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBG)
	@$(AR) $(NAME) $(OBG)

clean:
	@$(RM) $(OBG)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.SECONDARY: $(OBG)
.PHONY : all clean fclean re
.SILENT:
