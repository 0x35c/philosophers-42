# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulayus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 11:40:22 by ulayus            #+#    #+#              #
#    Updated: 2023/02/23 10:18:29 by ulayus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BONUS = philo_bonus

SRC = src/main.c src/ft_atoul.c src/parsing.c src/display.c\
	  src/routine.c src/manager.c\

CC = @clang

CFLAGS = -g -Wall -Wextra -Werror
LIBS = -pthread

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) ${OBJ} -o ${NAME} ${LIBS}
	@printf '\x1b[38;2;50;205;50mPhilo compiled 🤓\n\x1b[0m'

clean:
	@rm -f $(OBJ)
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mObjects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean: clean
	@rm -f ${NAME} 
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBinary removed\x1b[0m\e[5m 🚨\n\e[0m'

re: fclean all

.PHONY: all clean fclean re
