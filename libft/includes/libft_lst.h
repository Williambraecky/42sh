/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:57:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/21 11:23:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LST_H
# define LIBFT_LST_H

# include <string.h>

typedef struct s_list	t_list;
struct		s_list
{
	void	*content;
	size_t	content_size;
	t_list	*next;
};

t_list		*ft_lstnew(const void *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *n);
void		ft_lstiter(t_list *lst, void (*f)(t_list *));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void		ft_lstpushback(t_list **alst, const void *content,
		size_t content_size);
t_list		*ft_lstlast(t_list **alst);
void		ft_lstremoveif(t_list **alst, void *data_ref,
		int (*cmp)());
void		ft_lstsortinsert(t_list **begin_list, void *content, size_t size,
		int (*cmp)());
size_t		ft_lstlen(t_list *list);

#endif
