/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:18:18 by crobot            #+#    #+#             */
/*   Updated: 2021/12/17 13:18:20 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_quote_skipper(char *line, int *i, int j)
{
	t_ts	ts;

	ts.s1 = ft_substr(line, 0, j);
	ts.s2 = ft_substr(line, j + 1, *i - j - 1);
	ts.s3 = ft_strdup(line + *i + 1);
	free(line);
	ts.s4 = ft_strjoin(ts.s1, ts.s2);
	if (!ts.s4)
		return (free_ts(ts));
	free(ts.s1);
	free(ts.s2);
	ts.s1 = ft_strjoin(ts.s4, ts.s3);
	if (!ts.s1)
		return (free_ts(ts));
	free(ts.s3);
	free(ts.s4);
	*i -= 1;
	return (ts.s1);
}

char	*ft_quote_handler(char *line, int *i)
{
	int	j;

	j = *i;
	while (line[++(*i)])
		if (line[*i] == '\'')
			break ;
	return (ft_quote_skipper(line, i, j));
}

char	*ft_2quotes_handler(char *line, int *i, char **env, int status)
{
	int	j;

	j = (*i)++;
	while (line[*i])
	{
		if (*(line + *i) == '$')
		{
			line = ft_dollar_handler(line, i, env, status);
			if (!line)
				return (NULL);
		}
		else if (line[*i] == '\"')
			break ;
		else
			(*i)++;
	}
	return (ft_quote_skipper(line, i, j));
}
