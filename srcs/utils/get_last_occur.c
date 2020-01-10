/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_occu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:24:49 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/10 15:54:39 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


char *get_last_occur(char *str, char c)
{
  int  i;

  i = ft_strlen(str) - 1;
  while (i >= 0)
  {
    if (str[i] == c)
      return ((str + i));
    --i;
  }
  return (NULL);
}
