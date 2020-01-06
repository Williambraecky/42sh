/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_vec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:36:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 17:37:47 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_VEC_H
# define LIBFT_VEC_H

# include "libft.h"

# ifndef VEC_DEF_SIZE
#  define VEC_DEF_SIZE 5
# endif

typedef struct s_vec	t_vec;

struct		s_vec
{
	void	**vec;
	size_t	size;
	size_t	size_max;
};

int			ft_vecinit(t_vec *vec);
int			ft_vecinit_size(t_vec *vec, size_t size);
size_t		ft_vecsize(t_vec *vec);
size_t		ft_vecmaxsize(t_vec *vec);
int			ft_vecresize(t_vec *vec, size_t new_size);
void		*ft_vecget(t_vec *vec, size_t pos);
void		*ft_vecgettop(t_vec *vec);
int			ft_vecpush(t_vec *vec, void *ptr);
int			ft_vecdel(t_vec *vec, size_t pos);
int			ft_vecnpush(t_vec *vec, size_t n, ...);
int			ft_veccpush(t_vec *vec, void *ptr, size_t size_ptr);
void		*ft_vecpop(t_vec *vec);
int			ft_vecset(t_vec *vec, void *ptr, size_t pos);
void		ft_vecfree(t_vec *vec);
void		ft_veciter(t_vec *vec, void (*func_ptr)());
void		ft_veciteri(t_vec *vec, void (*func_ptr)(void *, size_t));
int			ft_vecput(t_vec *vec, void *ptr, size_t pos);
void		ft_vecdestroy(t_vec *vec, void (*func_ptr)());
void		ft_vecsort(t_vec *vec, int (*cmp)());

void		default_vec_destroy_function(void *ptr);

# ifndef DEFAULT_VEC_DESTROY
#  define DEFAULT_VEC_DESTROY default_vec_destroy_function
# endif

#endif
