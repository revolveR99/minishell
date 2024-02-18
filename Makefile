# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 15:39:40 by zabdulza          #+#    #+#              #
#    Updated: 2024/01/14 21:57:36 by kryxaurus        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation Flags
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -I/usr/local/opt/readline/include/
LFLAGS = -L/usr/local/opt/readline/lib -lreadline

# Project Files
NAME = minishell
HEADER = minishell.h
SRCS = $(wildcard src/*.c src/**/*.c)
OBJS = $(SRCS:.c=.o)

# Compile each C source file into an object file
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files to create the final executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

# Standard Rules
all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Custom Rules
norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS)
	norminette -R CheckForbiddenSourceHeader $(HEADER)

# needs to be recognized by the version of valgrind btw
val:
	valgrind --leak-check=full --trace-children=yes --track-fds=yes --ignore-fn=readline ./$(NAME)

.PHONY: all clean fclean re norm val