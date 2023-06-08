# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 14:29:49 by shinckel          #+#    #+#              #
#    Updated: 2023/06/08 15:18:39 by shinckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iheader -g  
# -fsanitize=address -g 

SRC := src/*.c
LIBFT := libft_functions/*.c

# Define colors
LIGHT := \033[1;43m
YELLOW := \033[1;103m
RESET := \033[0m

all:
		$(CC) $(CFLAGS) $(LIBFT) $(SRC) -o $(NAME)
		@echo "$(YELLOW) Compiled $(RESET)"
	 
clean:
		find . -type f -name "*.txt" ! -name "grocery_list.txt" -exec rm -f {} +
		@echo "$(LIGHT) Clean .txt files $(RESET)"

fclean: clean
		rm -rf $(NAME)
		@echo "$(LIGHT) Clean all $(RESET)"

re: fclean all
		@echo "$(LIGHT) Rebuild $(RESET)"
	

.PHONY: all clean fclean re