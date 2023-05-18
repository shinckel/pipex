# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 14:29:49 by shinckel          #+#    #+#              #
#    Updated: 2023/05/18 18:13:42 by shinckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iheaders/

SOURCE := srcs/*.c
LIBFT := libft/*.c
PRINTF := printf/*.c

all:	
		$(CC) $(CFLAGS) $(LIBFT) $(SOURCE) -o $(NAME)
	 
clean:

fclean: clean
		rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re