# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 19:52:35 by yorlians          #+#    #+#              #
#    Updated: 2023/06/30 14:00:36 by yorlians         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME		=	philo

CC			= 	cc
RM			=   rm -f
CFLAGS		=	-pthread -Wall -Werror -Wextra #-fsanitize=thread -g

SRCS		=	philo.c arguments_check.c utils.c display_message.c time.c \
				initialize.c control.c routine.c destroy_and_free.c
OBJS		=	$(SRCS:.c=.o)

BLUE		=	\033[0;94m
GREEN		=	\033[0;32m
RESET		=	\033[0m

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			echo "$(GREEN)✅🚀 Program compiled successfully 🚀✅$(RESET)"

clean:
			$(RM) $(OBJS)
			echo "$(BLUE)✨🧹🧺✨ Removed object files ✨🧺🧹✨$(RESET)"

fclean:		clean
			$(RM) $(NAME)
			echo "$(BLUE)✨💦🛁✨ Removed executable ✨🛁💦✨$(RESET)"
	
re:			fclean all

.PHONY:		all clean fclean re