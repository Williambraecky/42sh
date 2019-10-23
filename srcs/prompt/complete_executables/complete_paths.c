/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:48:40 by ntom              #+#    #+#             */
/*   Updated: 2019/10/23 16:41:03 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			search_path_complete
	(t_sh *shell, t_prompt *prompt, char **bins, char ***bins_complete)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (bins[i])
	{
		if (ft_strstartswith(bins[i], prompt->buffer) == 1)
			*bins_complete[j++] = bins[i];
		i++;
	}
	return (SH_ERR_NOEXIST);
}
