/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backspace_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 23:02:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:13:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			handle_backspace_search(t_prompt *prompt, char *buffer, t_sh *shell)
{
	size_t	index_backup;
	char	*histo;

	(void)buffer;
	if (prompt->search_buffer.size == 0)
	{
		ring_bell();
		return (SH_SUCCESS);
	}
	index_backup = prompt->query.curr_index;
	prompt->query.query = prompt->search_buffer.buffer;
	if ((histo = hquery_cnext(shell, &prompt->query)) != prompt->query.orig)
	{
		prompt->query.query = NULL;
		if (search_render_found(prompt, histo))
			return (SH_ERR_MALLOC);
		search_render(prompt);
		return (SH_SUCCESS);
	}
	prompt->query.query = NULL;
	prompt->query.curr_index = index_backup;
	buff_remove(&prompt->search_buffer, prompt->search_buffer.size - 1);
	prompt->query.curr_index = shell->history.size + 1;
	return (search_history(prompt, shell));
}
