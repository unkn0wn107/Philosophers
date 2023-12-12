# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 00:01:07 by agaley            #+#    #+#              #
#    Updated: 2023/12/11 17:15:40 by agaley           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR = obj

SRC = main.c
SRCS = simulation.c philosopher.c philo_check.c fork.c logger.c utils.c utils_type.c
H = philosopher.h
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

MAKEFLAGS += --no-print-directory
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
OBJ_FLAGS = ${CFLAGS}
CC = gcc

all:					${NAME}

${NAME}:				mkdir ${OBJ} ${OBJS} $(H)
		${CC} ${CFLAGS} ${OBJ} ${OBJS} -lpthread -o $@

$(OBJ_DIR)/%.o:			%.c $(H)
		$(CC) $(OBJ_FLAGS) -o $@ -c $<

mem:					$(NAME)
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo

check:
		norminette

static:					fclean
		csbuild -c make

mkdir:
		@mkdir -p $(OBJ_DIR)

clean:
		find . -name "${NAME}" -delete
		find . -name "*.gch" -delete

fclean:					clean
		find . -type d -name "${OBJ_DIR}" -exec rm -rf {} +

re:						fclean all

.PHONY:	all clean fclean re
