/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_wstr.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:25:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 20:43:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_WSTR_H
# define LIBFT_WSTR_H

# include "libft.h"

size_t	ft_wstrlen(char *str);
char	*ft_wstrindex(char *str, size_t index);
char	*ft_wstrsub(char *str, size_t start, size_t len);
size_t	ft_wstrfromindex(char *str, size_t index);

#endif
