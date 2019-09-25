/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_put.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:03:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 11:09:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PUT_H
# define LIBFT_PUT_H

# include <string.h>

void		ft_putchar_fd(int c, int fd);
void		ft_putchar(int c);
void		ft_putstr_fd(const char *str, int fd);
void		ft_putstr(const char *str);
void		ft_putendl_fd(const char *str, int fd);
void		ft_putendl(const char *str);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr(int n);
void		ft_putnstr_fd(const char *str, size_t len, int fd);
void		ft_putnstr(const char *str, size_t len);
void		ft_putnchar_fd(int c, int fd, size_t amount);
void		ft_putnchar(int c, size_t amount);

#endif
