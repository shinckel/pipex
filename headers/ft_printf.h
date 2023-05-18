/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinckel <shinckel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:15:50 by shinckel          #+#    #+#             */
/*   Updated: 2022/12/08 15:47:28 by shinckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define DEC "0123456789"
# define HEX_U "0123456789ABCDEF"
# define HEX_L "0123456789abcdef"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
/* <stdarg.h> has a bunch of macros that help me to access the printf arguments;
 * macro= code that is replaced by the value of the macro(using #define)...;
 *...just as DEC, HEC_U and HEX_L;
*/

int	ft_printf(const char *fmt, ...);
/* <variadic function> output formatting, writes the string pointed by format;
 * the format string(fmt) tells me what else is coming, it is all you need...
 * ...to call the variadic function!
*/

#endif