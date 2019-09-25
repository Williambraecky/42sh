/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 16:40:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 15:58:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>

# define ZERO (1 << 0)
# define MINUS (1 << 1)
# define BLANK (1 << 2)
# define PLUS (1 << 3)
# define HASHTAG (1 << 4)
# define ARGED_WIDTH (1 << 5)
# define ARGED_PRECISION (1 << 6)
# define LENGTH_Z (1 << 7)
# define LENGTH_J (1 << 8)
# define POINTER (1 << 9)
# define PRECISION (1 << 10)
# define DOUBLE_L (1 << 11)

# define UNDEFINED_WIDTH 0

# define PRINTF_BUFFER 4096

typedef struct s_printf	t_flags;
struct		s_printf
{
	short	flags;
	int		width;
	int		precision;
	int		longnb;
	int		shortnb;
	int		arg_pos;
	int		printed;
	char	*str;
};

typedef struct s_handler	t_handler;
struct		s_handler
{
	char	c;
	void	(*handler)(va_list *, t_flags *);
};

int			ft_printf(const char *str, ...);
int			ft_printf_fd(int fd, const char *str, ...);
void		ft_parse_printf(char *str, va_list *list, t_flags *flags);
void		ft_handle_colors(char **str, t_flags *flags);
t_flags		*ft_new_flags(void);
void		ft_parse_flags(char **str, va_list *list, t_flags *flags);
int			ft_read_star_flag(char **str, va_list *list);
t_flags		*ft_reset_flags(t_flags *flags);

void		ft_printf_putchar(int c, t_flags *printed);
void		ft_printf_putnchar(int c, t_flags *printed, size_t amount);
void		ft_printf_putnstr(const char *str, size_t len, t_flags *printed);
void		ft_printf_putstr(const char *str, t_flags *printed);
void		ft_printf_flush(t_flags *flags);

void		ft_handle(char **str, va_list *list, t_flags *flags);
uintmax_t	ft_unsigned_int(va_list *list, t_flags *flags);
intmax_t	ft_signed_int(va_list *list, t_flags *flags);
void		*ft_arg_for(va_list *list, t_flags *flags);
void		ft_printf_handle_string_intern(char *str, t_flags *flags);
void		ft_printf_handle_int(va_list *list, t_flags *flags);
void		ft_printf_handle_intlong(va_list *list, t_flags *flags);
void		ft_printf_handle_string(va_list *list, t_flags *flags);
void		ft_printf_handle_stringlong(va_list *list, t_flags *flags);
void		ft_printf_handle_char(va_list *list, t_flags *flags);
void		ft_printf_handle_charlong(va_list *list, t_flags *flags);
void		ft_printf_handle_none(int c, t_flags *flags);
void		ft_printf_handle_pointer(va_list *list, t_flags *flags);
void		ft_printf_handle_printed(va_list *list, t_flags *flags);
void		ft_printf_handle_octal(va_list *list, t_flags *flags);
void		ft_printf_handle_octallong(va_list *list, t_flags *flags);
void		ft_printf_handle_hexa_low(va_list *list, t_flags *flags);
void		ft_printf_handle_hexa_high(va_list *list, t_flags *flags);
void		ft_printf_handle_unsigned(va_list *list, t_flags *flags);
void		ft_printf_handle_unsignedlong(va_list *list, t_flags *flags);
void		ft_printf_handle_float(va_list *list, t_flags *flags);

char		*ft_printf_itoa(ssize_t value, size_t base, t_flags *flags);
char		*ft_printf_uitoa(size_t value, size_t base, t_flags *flags);
void		ft_handle_wint_t(wint_t c, t_flags *flags);
size_t		ft_wintt_len(wint_t c);
#endif
