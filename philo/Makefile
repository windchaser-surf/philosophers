# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 12:43:53 by fwechsle          #+#    #+#              #
#    Updated: 2024/01/29 16:06:33 by fwechsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC			=	src/init.c src/main.c src/threads.c src/utils.c src/mutex.c \
				src/logic.c src/utils_2.c src/init_utils.c

OBJS		= $(SRC:.c=.o)

CC			= cc

CFLAGS		= -Wall -Werror -Wextra

RM			= rm -rf

all: $(NAME) 

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)


fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re