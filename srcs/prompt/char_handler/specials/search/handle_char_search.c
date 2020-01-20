/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 23:00:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 00:26:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: basically we need to add to the search buffer and do another search
*/

int			handle_char_search(t_prompt *prompt, char *buffer, t_sh *shell)
{
	if (buff_insert(&prompt->search_buffer, buffer,
		prompt->search_buffer.size) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	prompt->query.curr_index = shell->history.size + 1;
	return (search_history(prompt, shell));
}
