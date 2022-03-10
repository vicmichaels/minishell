/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:43:34 by crobot            #+#    #+#             */
/*   Updated: 2022/02/17 17:43:36 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_digit_handler(char *line, int *i, int j)
{
	t_ts	ts;

	ts.s1 = ft_substr(line, 0, j);
	ts.s2 = ft_strdup(line + *i + 2);
	ts.s3 = ft_strjoin(ts.s1, ts.s2);
	if (!ts.s3)
		return (free_ts(ts));
	free(line);
	free(ts.s1);
	free(ts.s2);
	*i = j;
	return (ts.s3);
}

char	*ft_query_handler(char *line, int *i, int status)
{
	t_ts	ts;

	ts.s1 = ft_substr(line, 0, *i);
	ts.s2 = ft_itoa(status);
	ts.s3 = ft_strdup(&line[*i + 2]);
	ts.s4 = ft_strjoin(ts.s1, ts.s2);
	if (!ts.s4)
		return (free_ts(ts));
	free(line);
	*i = ft_strlen(ts.s4);
	free(ts.s1);
	ts.s1 = ft_strjoin(ts.s4, ts.s3);
	if (!ts.s1)
		return (free_ts(ts));
	free(ts.s2);
	free(ts.s3);
	free(ts.s4);
	return (ts.s1);
}

char	*ft_key_extractor(char *line, char **env, int len)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], line, len) == env[i] && env[i][len] == '=')
			break ;
	if (!env[i])
		return (NULL);
	return (ft_strdup(env[i]));
}

char	*ft_dollar_handler2(char *line, int *i, int j, char **env)
{
	char	*key;
	t_ts	ts;
	int		len;

	ts = ft_write_ts(line, i, j);
	len = (int)ft_strlen(ts.s2);
	if (len == 0)
	{
		free_ts(ts);
		return (line);
	}
	free(line);
	key = ft_key_extractor(ts.s2, env, (int)ft_strlen(ts.s2));
	if (!key)
		return (ft_no_key(ts, i, j));
	free(ts.s2);
	ts.s2 = ft_strchr(key, key[len + 1]);
	line = ft_strjoin(ts.s1, ts.s2);
	free(key);
	*i = (int)ft_strlen(line);
	free(ts.s1);
	ts.s1 = ft_strjoin(line, ts.s3);
	free(line);
	free(ts.s3);
	return (ts.s1);
}

char	*ft_dollar_handler(char *line, int *i, char **env, int status)
{
	int	j;

	j = *i;
	if (ft_isdigit(line[*i + 1]))
		return (ft_digit_handler(line, i, j));
	if (line[*i + 1] == '?')
		return (ft_query_handler(line, i, status));
	while (line[++(*i)])
		if (!ft_isalnum(line[*i]) || line[*i] == '_')
			break ;
	if (*i == j + 1)
		return (line);
	return (ft_dollar_handler2(line, i, j, env));
}
