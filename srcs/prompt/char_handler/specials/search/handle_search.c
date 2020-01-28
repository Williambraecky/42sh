/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:44:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/28 14:02:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			search_history(t_prompt *prompt, t_sh *shell)
{
	char	*histo;
	size_t	i;
	int		ret;

	histo = NULL;
	i = prompt->query.curr_index;
	prompt->query.query = prompt->search_buffer.buffer;
	histo = hquery_cprev(shell, &prompt->query);
	prompt->query.query = NULL;
	prompt->search_found = histo != NULL;
	if (histo != NULL && (ret = search_render_found(prompt, histo)))
		return (ret);
	search_render(prompt);
	return (SH_SUCCESS);
}

int			handle_search(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)buffer;
	if (prompt->searching == 0)
	{
		prompt->search_found = 1;
		prompt->searching = 1;
		buff_clear(&prompt->search_buffer);
		search_render(prompt);
		prompt->query.curr_index = shell->history.size + 1;
		if (!(prompt->query.orig = ft_strdup(prompt->buffer.buffer)))
			return (SH_ERR_MALLOC);
		return (SH_SUCCESS);
	}
	return (search_history(prompt, shell));
}
