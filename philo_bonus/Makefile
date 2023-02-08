# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 17:38:06 by axlamber          #+#    #+#              #
#    Updated: 2023/02/08 16:52:04 by axlamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addsuffix .c, main)
OBJS	= $(SRCS:%.c=.build/%.o)

NAME	= philosophers
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g
HEADERS = -I includes/ -I libft/includes/
LIBFT = -L libft/ -lft

flag:=1
.build/%.o : %.c
		@if [ $(flag) = "1" ]; then\
			clear ;\
			printf "\033[1;35m========================================\n";\
			printf "|         PHILOSOPHERS LOADING         |\n";\
			printf "========================================\n";\
			printf "|                                      |\n";\
			printf "|                                      |\n\033[A\033[A";\
		fi
		@setterm -cursor off
		@mkdir -p .build
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
		@printf "\033[1;32m|\033[32m                                      \033[m\r"
		@printf "\033[32mCompiling $@... \033[m\r"

$(NAME):$(OBJS)
		@printf "\033[K\033[1;32m| Philosophers : compiled              |\n\033[m"
		@make --no-print-directory -C libft/
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
		@printf "\033[1;32m========================================\n"
		@printf "|         COMPILATION FINISHED !       |\n"
		@printf "========================================\n\033[m"
		@setterm -cursor on

all: $(NAME)

clean:
			@printf "\033[1;31m========================================\n"
			@printf "|         PHILOSOPHERS CLEANING        |\n"
			@printf "========================================\n\033[m"
			@printf "\033[K\033[1;31m|\033[1;33m Destroying objects                   \033[1;31m|\n\033[m"
			@make --no-print-directory clean -C libft/
			@$(RM) .build

fclean:	clean
			@printf "\033[K\033[1;31m|\033[1;31m Destroying all                       \033[1;31m|\n\033[m"
			@make --no-print-directory fclean -C libft/
			@$(RM) .build $(NAME)
			@printf "\033[1;31m========================================\n\033[m"

re:		fclean all

.PHONY: all clean fclean re 
