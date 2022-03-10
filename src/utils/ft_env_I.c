/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_I.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:50:36 by crobot            #+#    #+#             */
/*   Updated: 2022/02/17 16:50:37 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(t_data *data, char *key)
{
	t_env	*first;
	char	*ret;

	ret = NULL;
	first = data->env;
	while (first && (ft_strcmp(key, first->key)))
		first = first->next;
	if (first)
		ret = first->value;
	return (ret);
}

t_env	*find_env(t_data *data, char *key)
{
	t_env	*ret;

	ret = data->env;
	while (ret && (ft_strcmp(key, ret->key)))
		ret = ret->next;
	return (ret);
}

int	ft_split_env(char *param, char **key, char **value)
{
	char	*t;
	char	*s;

	s = ft_strdup(param);
	if (!s)
		return (12);
	t = ft_strchr(s, (int) '=');
	if (!t)
	{
		free(s);
		return (22);
	}
	*value = ft_strdup(t + 1);
	if (!*value)
		return (12);
	t = ft_substr(s, 0, (t - s));
	if (!t)
		return (12);
	*key = ft_strdup(t);
	if (!*key)
		return (12);
	free(s);
	free(t);
	return (0);
}

int	ft_split_env_m(char *param, char **key, char **value)
{
	char	*t;
	char	*s;

	s = ft_strdup(param);
	if (!s)
		return (12);
	t = ft_strchr(s, (int) '+');
	*value = ft_strdup(t + 2);
	if (!*value)
		return (12);
	t = ft_substr(s, 0, t - s);
	if (!t)
		return (12);
	*key = ft_strdup(t);
	if (!*key)
		return (12);
	free(s);
	free(t);
	return (0);
}
