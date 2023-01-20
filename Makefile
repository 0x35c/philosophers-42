# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulayus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 11:40:22 by ulayus            #+#    #+#              #
#    Updated: 2023/01/20 16:35:05 by ulayus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BONUS = philo_bonus

SRC = src/main.c src/ft_atol.c src/parsing.c src/display.c\

SRC_B = \

CC = @clang

CFLAGS = -g -Wall -Wextra -Werror
LIBS = -pthread

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

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

bonus: ${BONUS}

${BONUS}: ${OBJ_B}
	$(CC) ${OBJ_B} -o ${BONUS} ${LIBS}
	@printf '\x1b[38;2;50;205;50mPhilo bonus compiled 🤓\n\x1b[0m'

clean_b:
	@rm -f $(OBJ_B)
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mBonus objects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean_b: clean_b
	@rm -f ${BONUS} 
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBonus binary removed\x1b[0m\e[5m 🚨\n\e[0m'

re_b: fclean_b bonus

.PHONY: all clean fclean re bonus clean_b fclean_b re_b
