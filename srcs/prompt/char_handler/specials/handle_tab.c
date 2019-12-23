/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 15:56:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_tab(t_prompt *prompt, char *buffer, t_sh *shell)
{
	char	*line;
	t_vec	poss;

	line = prompt->buffer.buffer;
	if(ft_vecinit(&poss))
		return (SH_ERR_MALLOC);
	autocomplete_command(line, shell, &poss);
	for (size_t i = 0; i < poss.size; i++)
		ft_printf("vec[%d] = %s\n", i, ft_vecget(&poss, i));
//	order_vector(&poss);
	(void)buffer;
//	if (poss.size == 0)
//	{
//		*buffer = ' ';									/*
//		handle_new_char(prompt, buffer, shell);			** valid poss();
//		return (RET_CONT);								*/ dans le cas ou
//	}
	//free_vec();
	return (RET_CONT);
}
