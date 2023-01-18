# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 17:38:06 by axlamber          #+#    #+#              #
#    Updated: 2023/01/18 17:00:29 by axlamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addsuffix .c, main parsing utils philo)
OBJS	= $(SRCS:%.c=.build/%.o)

NAME	= philosophers
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror
HEADERS = -I includes/ -I libft/includes/
LIBFT = -L libft/ -lft

.build/%.o : %.c
		@setterm -cursor off
		@mkdir -p .build
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
		@printf "\033[32mCompiling $@... \033[K\033[m\r"

$(NAME):$(OBJS)
		@make --no-print-directory -C libft/
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
		@printf "\033[K\033[1;32m Philosophers : compiled\n\033[m"
		@setterm -cursor on

all: $(NAME)

clean:
			@printf "\033[K\033[1;33m Destroying objects\n\033[m"
			@make --no-print-directory clean -C libft/
			@$(RM) .build

fclean:	clean
			@printf "\033[K\033[1;31m Destroying all\n\033[m"
			@make --no-print-directory fclean -C libft/
			@$(RM) .build

re:		fclean all

.PHONY: all clean fclean re 