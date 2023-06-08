# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 14:29:49 by shinckel          #+#    #+#              #
#    Updated: 2023/06/08 20:34:06 by shinckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iheader -g
#CFLAGS += -fsanitize=address

SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# Define colors
RED := \033[1;41m
YELLOW := \033[1;103m
RESET := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(YELLOW) Pipex compiled $(RESET)"

clean:
	find . -type f -name "*.txt" ! -name "grocery_list.txt" -exec rm -f {} +
	@echo "$(RED) Clean .txt files $(RESET)"
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)
	@echo "$(RED) Clean all $(RESET)"

re: fclean all

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean_libft:
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: all clean fclean re clean_libft
