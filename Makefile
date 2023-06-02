# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 14:29:49 by shinckel          #+#    #+#              #
#    Updated: 2023/06/01 21:35:09 by shinckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g -Iheaders 

SOURCE := src/*.c
LIBFT := libft_functions/*.c

all:	
		$(CC) $(CFLAGS) $(LIBFT) $(SOURCE) -o $(NAME)
	 
clean:

fclean: clean
		rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re