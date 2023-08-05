# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 18:10:53 by pboonpro          #+#    #+#              #
#    Updated: 2023/08/05 18:17:48 by pboonpro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = meaw.c util.c\

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread #-fsanitize=address

CC = cc

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
