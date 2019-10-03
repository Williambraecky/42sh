/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:55:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/28 18:49:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_INT_H
# define LIBFT_INT_H

# include <string.h>

# define LIB_CHAR_BIT 8
# define LIB_SCHAR_MIN -128
# define LIB_SCHAR_MAX 127
# define LIB_UCHAR_MAX 255
# define LIB_CHAR_MIN -128
# define LIB_CHAR_MAX 127
# define LIB_MB_LEN_MAX 16
# define LIB_SHRT_MIN -32768
# define LIB_SHRT_MAX 32767
# define LIB_USHRT_MAX 65535
# define LIB_INT_MIN -2147483648
# define LIB_INT_MAX 2147483647
# define LIB_UINT_MAX 4294967295
# define LIB_LONG_MIN -9223372036854775808L
# define LIB_LONG_MAX 9223372036854775807L
# define LIB_ULONG_MAX 18446744073709551615L

int			ft_atoi(const char *str);
long		ft_atol(const char *str);
char		*ft_itoa_base(ssize_t value, size_t basesize);
char		*ft_itoa(ssize_t n);
char		*ft_uitoa_base(size_t value, size_t basesize);
char		*ft_uitoa(size_t value);
char		ft_itoc_base(ssize_t value, size_t basesize);
char		ft_itoc(ssize_t value);
size_t		ft_intlen_base(ssize_t value, size_t basesize);
size_t		ft_intlen(ssize_t value);
size_t		ft_uintlen_base(size_t n, size_t basesize);
size_t		ft_uintlen(size_t n);
int			*ft_range(int min, int max);
int			ft_intmin(int len, ...);
int			ft_intmax(int len, ...);
int			ft_min(int i, int j);
int			ft_max(int i, int j);
int			ft_abs(int i);
void		ft_swapint(int *a, int *b);
void		ft_swapshort(short *a, short *b);
void		ft_swaplong(long *a, long *b);
int			ft_intcmp(int a, int b);
void		ft_intsort(int *tab, size_t len, int (*cmp)());

#endif
