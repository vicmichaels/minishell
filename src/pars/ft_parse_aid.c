/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_aid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:54:07 by crobot            #+#    #+#             */
/*   Updated: 2022/02/17 17:54:10 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_empty(char c)
{
	if (c == '\0' || c == 9 || c == 32)
		return (TRUE);
	return (FALSE);
}

int	ft_special_symbol(char c, int i, int j)
{
	if (((i == j) && (c == 32 || c == 9))
		|| c == '$' || c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

int	ft_space_skipper(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] != 9 && line[*i] != 32)
			break ;
		(*i)++;
	}
	return (*i);
}

char	*ft_no_key(t_ts ts, int *i, int j)
{
	ts.s2 = ft_strjoin(ts.s1, ts.s2);
	if (!ts.s2)
		return (free_ts(ts));
	free(ts.s1);
	free(ts.s3);
	*i = j;
	return (ts.s2);
}
