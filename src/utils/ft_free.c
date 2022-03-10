/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:10:25 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 12:10:27 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_2d_arr(char **p)
{
	size_t	i;

	if (p == NULL)
		return (p);
	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	free(p);
	p = NULL;
	return (NULL);
}

void	ft_free_at_exit(t_data *data)
{
	t_cmd	*cmd_tmp;

	if (data->line)
		free(data->line);
	data->line = NULL;
	while (data->first_cmd != NULL)
	{
		cmd_tmp = data->first_cmd;
		if (data->first_cmd->fd_in != 0)
			close(data->first_cmd->fd_in);
		if (data->first_cmd->fd_out != 1)
			close(data->first_cmd->fd_out);
		if (data->first_cmd->pipe_in)
			data->first_cmd->pipe_in = NULL;
		if (data->first_cmd->pipe_out)
			data->first_cmd->pipe_out = NULL;
		if (data->first_cmd->arg)
			free_2d_arr(data->first_cmd->arg);
		data->first_cmd = data->first_cmd->next;
		free(cmd_tmp);
	}
}

void	ft_free_key_value(char **key, char **value)
{
	free(*key);
	free(*value);
	*key = NULL;
	*value = NULL;
}

char	*free_ts(t_ts ts)
{
	if (ts.s1)
		free (ts.s1);
	if (ts.s2)
		free (ts.s2);
	if (ts.s3)
		free (ts.s3);
	if (ts.s4)
		free (ts.s4);
	return (NULL);
}
