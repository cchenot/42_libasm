# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchenot <cchenot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 15:33:57 by cchenot           #+#    #+#              #
#    Updated: 2020/05/05 15:34:00 by cchenot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

SRCS =	ft_read.s		\
		ft_write.s		\
		ft_strcmp.s		\
		ft_strcpy.s		\
		ft_strdup.s		\
		ft_strlen.s		\

OBJS = $(SRCS:.s=.o)

CC = clang

FLAGS = -Wall -Wextra -Werror

%.o: %.s
		nasm -felf64 $< -o $@

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

all: $(NAME)

test: $(NAME) test.c
		$(CC) $(FLAGS) -o test_libasm test.c $(NAME)
		mkdir -p ./testdir

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)
		rm -f test_libasm
		rm -rf ./testdir

re: fclean all

phony: all clean fclean re
