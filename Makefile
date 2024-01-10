# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 15:07:56 by joao-ppe          #+#    #+#              #
#    Updated: 2024/01/10 22:26:29 by joao-ppe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -g3 -fsanitize=thread -O3 -march=native
#CFLAGS = -Wall -Wextra -Werror -g
NAME = philo

SRC = src/main.c src/utils.c src/verifications.c src/init.c src/routine.c src/routine_utils.c src/actions.c src/free.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all