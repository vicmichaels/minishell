/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:38:06 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 11:38:08 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_handler(t_data *data, char *line, int *i, int *j)
{
	if (*i == *j && !data->cmd->arg[0] && data->cmd->fd_in == 0
		&& data->cmd->fd_out == 1)
	{
		data->ret_val = ER_SYNTAX;
		printf("minishell: syntax error\n");
		return ;
	}
	if (*i != *j && ft_get_com_args(data, line, i, j) != OK)
		return ;
	(*i)++;
	if (line[*i] == '|')
		(*i)++;
	*j = *i;
	data->pipe++;
	data->cmd->next = ft_cmd_init();
	if (!data->cmd->next)
	{
		data->ret_val = ER_MALLOC;
		return ;
	}
	data->ret_val = 0;
	data->cmd = data->cmd->next;
}
