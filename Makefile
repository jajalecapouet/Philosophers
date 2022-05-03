# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 10:44:06 by njaros            #+#    #+#              #
#    Updated: 2022/05/03 19:15:30 by njaros           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
<<<<<<< HEAD
FLAGS = -Wall -Wextra -Werror -pthread
=======
FLAGS = -Wall -Wextra -Werror -fsanitize=thread
>>>>>>> 7f27015954559e6f1d0a7d2af017d27199126d19

PATH_SRCS = src
PATH_OBJS = obj
PATH_INCLUDES = includes

LST_SRCS =	philo.c \
			philo_parsing_utils.c \
			time_utils.c \
			philo_utils.c \
			philo_utils2.c \
			philo_utils3.c \
			free.c
LST_OBJS =	${LST_SRCS:.c=.o}
LST_INCLUDES =	philo.h

SRC =		$(addprefix ${PATH_SRCS}/,${LST_SRCS})
OBJS =		$(addprefix ${PATH_OBJS}/,${LST_OBJS})
INCLUDES =	$(addprefix ${PATH_INCLUDES}/,${LST_INCLUDES})

all :				${NAME} Makefile

${NAME} :			${OBJS}
					${CC} ${FLAGS} ${OBJS} -o $@

${PATH_OBJS}/%.o:	${PATH_SRCS}/%.c ${INCLUDES} Makefile | ${PATH_OBJS}
					${CC} ${FLAGS} -c $< -o $@ -I ${PATH_INCLUDES}

${PATH_OBJS}:
					mkdir obj

clean :
					rm -rf obj

fclean :			clean
					rm ${NAME}

re :				fclean all

.PHONY: all re clean fclean