/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:03:33 by shinckel          #+#    #+#             */
/*   Updated: 2022/11/28 12:46:40 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/* <ctype.h> checks for an alphabetic character*/
int		ft_isalpha(int c);
/* <ctype.h> checks for a digit (0 through 9)*/
int		ft_isdigit(int c);
/* <ctype.h> checks for an alphanumeric character*/
int		ft_isalnum(int c);
/* <ctype.h> checks whether c fits into the ASCII character set*/
int		ft_isascii(int c);
/* <ctype.h> checks for any printable character*/
int		ft_isprint(int c);
/* <ctype.h> convert char to uppercase*/
int		ft_toupper(int c);
/* <ctype.h> convert char to lowercase*/
int		ft_tolower(int c);

/* <string.h> fill memory with a constant byte*/
void	*ft_memset(void *b, int c, size_t len);
/* <string.h> zero a byte string, it writes n zeroed bytes to the string s*/
void	ft_bzero(void *s, size_t n);
/* <string.h> calculate the length of a string*/
size_t	ft_strlen(const char *s);
/* <string.h> copy memory area, it returns the original value of dst.*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
/* <string.h> same as memcpy, more secure when dst and src might overlap*/
void	*ft_memmove(void *dst, const void *src, size_t len);
/* <string.h> copy string, returns string length it tried to create(src+NULL)*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
/* <string.h> concatenate to an specific size, returns length of dst+src+NULL*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/* <string.h> locate character in string, returns pointer first occurrence*/
char	*ft_strchr(const char *s, int c);
/* <string.h> same as strchr, last occurrence as extra r stands for reverse*/
char	*ft_strrchr(const char *s, int c);
/* <string.h> compare two strings, returns less, equal or more than 0*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* <string.h> find the first occurrence of a character in a buffer*/
void	*ft_memchr(const void *s, int c, size_t n);
/* <string.h> compare memory areas, same as strncmp but typecasting memory*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/* <string.h> locate a substring in a string, returns a pointer to big*/
char	*ft_strnstr(const char *big, const char *little, size_t len);
/* <string.h> creates a duplicate for the string passed as parameter*/
char	*ft_strdup(const char *s);

/* <stdlib.h> convert a string to an integer*/
int		ft_atoi(const char *str);
/* <stdlib.h> allocates memory and sets its bytes' values to 0*/
void	*ft_calloc(size_t nmemb, size_t size);

/* <non-standard> returns a substring from a string*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/* <non-standard> concatenates two strings*/
char	*ft_strjoin(char const *s1, char const *s2);
/* <non-standard> trims beginning and end of string with specific set of chars*/
char	*ft_strtrim(char const *s1, char const *set);
/* <non-standard> splits a string using a char as parameter*/
char	**ft_split(char const *s, char c);
/* <non-standard> converts a number into a string*/
char	*ft_itoa(int n);
/*<non-standard> applies a function to each character of a string*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/* <non-standard> same as ft_strmapi, but without using malloc and none return*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/* <non-standard> output a char to a file descriptor*/
void	ft_putchar_fd(char c, int fd);
/* <non-standard> output a string to a file descriptor*/
void	ft_putstr_fd(char *s, int fd);
/* <non-standard> output a string to a file descriptor, followed by a new line*/
void	ft_putendl_fd(char *s, int fd);
/* <non-standard> output a number to a file descriptor*/
void	ft_putnbr_fd(int n, int fd);

/* t_list struct declaration, so you don't need to define it in each file;
 * content = assign data in current node, next = link to the next one...;
 * ...therefore, each node stores the data and the address of the next node;
 *typedef= enables the user to create their own types(old type replaced by new);
 *...so, s_list is replaced by t_list;
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* <linked list> creates a new list's node*/
t_list	*ft_lstnew(void *content);
/* <linked list> adds a node(new) at the beginning of the list(lst)*/
void	ft_lstadd_front(t_list **lst, t_list *new);
/* <linked list> counts the number of nodes inside a list*/
int		ft_lstsize(t_list *lst);
/* <linked list> returns the address of the last node of the list*/
t_list	*ft_lstlast(t_list *lst);
/* <linked list> adds a node(new) at the end of the list(lst)*/
void	ft_lstadd_back(t_list **lst, t_list *new);
/* <linked list> frees the memory of node's content (through function 'del')*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));
/* <linked list> deletes and free list, same as ft_lstdelone but here is **lst*/
void	ft_lstclear(t_list **lst, void (*del)(void*));
/* <linked list> applies a function to each node of a list*/
void	ft_lstiter(t_list *lst, void (*f)(void *));
/* <linked list> same as lstiter, but creates and return a new list*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif