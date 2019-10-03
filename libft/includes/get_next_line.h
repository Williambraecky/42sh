/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:48:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/23 14:30:48 by jstraetm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>

# define BUFF_SIZE 256

typedef struct s_line	t_line;
struct		s_line
{
	int		fd;
	char	*str;
	size_t	size;
	size_t	remaining;
};

int			get_next_line(const int fd, char **line);
void		ft_clear_gnl(int fd);

#endif
