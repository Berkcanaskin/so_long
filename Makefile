# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baskin <baskin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 00:01:42 by baskin            #+#    #+#              #
#    Updated: 2025/01/23 03:04:04 by baskin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -Lminilibx-linux -lmlx -lX11 -lXext -lm

SRC_DIR = source/

SRC_FILES = map_check.c \
			map_parse.c \
			map_validate.c \
			utils_exit.c \
			utils_mem.c \
			utils_num.c \
			utils_string.c \
			draw.c \
			init.c \
			main.c \
			move.c \


SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))


OBJS = $(SRCS:.c=.o)


all: libs $(NAME)



$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(MLX) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libs:
	make -C ./minilibx-linux


clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re libs
