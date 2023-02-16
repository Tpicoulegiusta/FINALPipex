# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 09:58:45 by tpicoule          #+#    #+#              #
#    Updated: 2023/02/16 12:52:30 by tpicoule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_B		= pipexbonus
SOURCES		= pipex_utils.c \
			  pipex_utils_2.c \
			  pipex.c
SOURCES_B	= ./BONUS/pipex_bonus.c \
			  ./BONUS/pipex_utils_bonus.c \
			  ./BONUS/pipex_utils_2_bonus.c
OBJECTS_B	= ${SOURCES_B:.c=.o}
OBJECTS		= ${SOURCES:.c=.o}
RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJECTS}
		${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
		
${NAME_B}: 	${OBJECTS_B}
		${CC} ${CFLAGS} ${OBJECTS_B} -o ${NAME}

all: ${NAME}

bonus: ${NAME_B}

clean:
	${RM} ${OBJECTS}
	${RM} ${OBJECTS_B}

fclean: clean
	${RM} ${NAME}
	${RM} ${NAME_B}

re: fclean all

.PHONY: all clean fclean re
