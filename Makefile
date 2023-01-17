# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 17:38:06 by axlamber          #+#    #+#              #
#    Updated: 2023/01/17 18:20:11 by axlamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m


SRCS	= main.c
OBJS	= $(SRCS:%.c=build/%.o)
NAME	= philosophers
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror
HEADERS = -I includes/
LIBFT = -L libft/ -lft

build/%.o : %.c
		@echo "$(COLOUR_BLUE)		*------------------------*"
		@echo "$(COLOUR_BLUE)		|    Generating libft    |"
		@echo "$(COLOUR_BLUE)		*------------------------*"
		@make --no-print-directory -C libft/
		@mkdir -p build
		@echo "$(COLOUR_BLUE)		*------------------------*"
		@echo "$(COLOUR_BLUE)		|    Creating the .o     |"
		@echo "$(COLOUR_BLUE)		*------------------------*"
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)
			@echo "$(COLOUR_GREEN)		*------------------------*"
			@echo "$(COLOUR_GREEN)		|     Makefile DONE !    |"
			@echo "$(COLOUR_GREEN)		*------------------------*"


all: $(NAME)

clean:
			@echo "$(COLOUR_RED)		*------------------------*"
			@echo "$(COLOUR_RED)		|     Cleaning the .o    |"
			@echo "$(COLOUR_RED)		*------------------------*"
			@make --no-print-directory clean -C libft/
			@$(RM) build

fclean:	clean
			@echo "$(COLOUR_RED)		*------------------------*"
			@echo "$(COLOUR_RED)		|       Cleaning all     |"
			@echo "$(COLOUR_RED)		*------------------------*"
			@make --no-print-directory fclean -C libft/
			@$(RM) build

re:		fclean all

.PHONY: all clean fclean re 