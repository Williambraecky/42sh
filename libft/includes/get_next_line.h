/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:48:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/24 22:09:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 512

typedef struct		s_line
{
	int				fd;
	char			*str;
	size_t			size;
	size_t			remaining;
}					t_line;

int					get_next_line(const int fd, char **line);

#endif
