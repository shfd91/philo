# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 21:08:01 by sanghole          #+#    #+#              #
#    Updated: 2021/11/29 15:40:35 by sanghole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
DEBUG	= -g
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f
MAIN	= main
ASAN	= -g3 -fsanitize=address

NAME	= philo
NAME_B	= philo_bonus

SRC		= 	philo.c \
			utils.c \
			check_n_init.c \
			life_cycle.c \
			free_destory.c

SRC_B	=	 \

OBJ		=	${SRC:.c=.o}
OBJ_B	=	${SRC_B:.c=.o}

ifdef WITH_BONUS
	NAMES	= $(NAME_B)
	OBJS	= $(OBJ_B)
else
	NAMES	= $(NAME)
	OBJS	= $(OBJ)
endif

%.o 		: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@

all			: $(NAMES)

$(NAMES) : $(OBJS)
	$(CC) -g $(CFLAGS) $(CFLAGS) $(OBJS) -o $(NAMES)

bonus		:
	make WITH_BONUS=1 all

clean		:
	$(RM) *.o
	$(RM) bonus/*.o

fclean		: clean
	rm -rf philo

re			: fclean all

.PHONY		: all clean fclean re bonus