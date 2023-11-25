# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 11:42:29 by rmitache          #+#    #+#              #
#    Updated: 2023/10/28 03:19:37 by rmitache         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Output name
NAME = philo

# Source files
SRC = actions.c \
	get_info.c \
	init_and_state.c \
	meals_and_kill.c \
	parsing_and_other.c \
	philo.c \
	routines_and_joins.c \
	utils.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compilation
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
