/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:02:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 17:37:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEM_H
# define LIBFT_MEM_H

# include <string.h>

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *b, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memalloc(size_t t);
void	ft_memdel(void **ap);
void	ft_memswap(void *a, void *b, size_t len);
void	*ft_realloc(void *old, size_t old_size, size_t new_size);
void	*ft_memdup(void *ptr, size_t size);
void	*ft_calloc(size_t count, size_t size);
void	ft_ptrsort(void **tab, size_t len, int (*cmp)());

#endif
