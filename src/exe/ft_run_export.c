/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:29:49 by esylva            #+#    #+#             */
/*   Updated: 2022/02/10 15:16:01 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_export(t_data *data)
{
	char	*key;
	char	*value;

	value = NULL;
	key = NULL;
	if (!data->cmd->arg[1])
		ft_empty_export(data);
	else if (!ft_strnstr(data->cmd->arg[1], "+=",
			ft_strlen(data->cmd->arg[1])))
		ft_run_export1(data, key, value);
	else
		ft_run_export2(data, key, value);
	ft_free_key_value(&key, &value);
	ft_update_env(data);
}

void	ft_run_export1(t_data *data, char *key, char *value)
{
	data->ret_val = ft_split_env(data->cmd->arg[1], &key, &value);
	if (data->ret_val == 22)
	{
		key = ft_strdup(data->cmd->arg[1]);
		value = NULL;
		if (!key)
			return ;
	}
	if (data->ret_val == 12)
		return ;
	if (ft_iskey(key, data))
		return ;
	if (ft_do_export(data, key, value))
		return ;
}

void	ft_run_export2(t_data *data, char *key, char *value)
{
	t_env	*first;

	first = data->env;
	data->ret_val = ft_split_env_m(data->cmd->arg[1], &key, &value);
	if (data->ret_val == 12)
		return ;
	if (ft_iskey(key, data))
		return ;
	while (first && (ft_strcmp(key, first->key)))
		first = first->next;
	if (first)
	{
		first->value = ft_strjoin_m(first->value, value);
		if (!first->value)
			data->ret_val = 12;
	}
	else
	{
		first = NULL;
		first = ft_lstnew(data);
		if (!first)
			data->ret_val = 12;
		ft_lstadd_back(first, data, key, value);
	}
}

int	ft_do_export(t_data *data, char *key, char *value)
{
	t_env	*first;

	first = data->env;
	while (first && (ft_strcmp(key, first->key)))
		first = first->next;
	if (first)
	{
		if (first->value)
			free(first->value);
		if (!value)
			first->value = NULL;
		else
			first->value = ft_strdup(value);
		if (!first->value)
			return (12);
	}
	else
	{
		first = NULL;
		first = ft_lstnew(data);
		if (!first)
			return (12);
		ft_lstadd_back(first, data, key, value);
	}
	return (0);
}

void	ft_empty_export(t_data *data)
{
	t_env	*hd;

	hd = data->env;
	while (hd)
	{
		if (wr_fd(data->cmd->fd_out, "declare -x ", 11, data))
			return ;
		if (wr_fd(data->cmd->fd_out, hd->key, ft_strlen(hd->key), data))
			return ;
		if (hd->value)
		{				
			(wr_fd(data->cmd->fd_out, "=\"", 2, data));
			(wr_fd(data->cmd->fd_out, hd->value, ft_strlen(hd->value), data));
			(wr_fd(data->cmd->fd_out, "\"", 1, data));
		}
		(wr_fd(data->cmd->fd_out, "\n", 1, data));
		hd = hd->next;
	}
}
