/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:23:44 by crobot            #+#    #+#             */
/*   Updated: 2022/02/14 14:23:46 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_data *data, int **fd, int i)
{
	close(fd[i][1]);
	data->cmd->pipe_in = fd[i];
	data->cmd->pipe_out = fd[i + 1];
	ft_exec_pipe(data);
	close(fd[i][0]);
}

void	start_pipe(int *fd, t_data *data)
{
	data->cmd->pipe_in = NULL;
	data->cmd->pipe_out = fd;
	ft_exec_pipe(data);
}

void	end_pipe(int *fd, t_data *data)
{
	data->cmd->pipe_in = fd;
	data->cmd->pipe_out = NULL;
	ft_exec_pipe(data);
}

void	ft_redir_pipe(t_data *data)
{
	if (data->pipe > 1)
	{
		if (data->cmd->pipe_in != NULL)
		{
			if (data->cmd->fd_in == 0)
				if (dup2(data->cmd->pipe_in[0], STDIN_FILENO) == -1)
					return (ft_error(data, errno));
			close(data->cmd->pipe_in[1]);
		}
		if (data->cmd->pipe_out != NULL)
		{
			if (data->cmd->fd_out == 1)
				if (dup2(data->cmd->pipe_out[1], STDOUT_FILENO) == -1)
					return (ft_error(data, errno));
			close(data->cmd->pipe_out[0]);
		}
	}
	if (dup2(data->cmd->fd_out, STDOUT_FILENO) == -1)
		return (ft_error(data, errno));
	if (dup2(data->cmd->fd_in, STDIN_FILENO) == -1)
		return (ft_error(data, errno));
}

void	ft_pipe_work(t_data *data)
{
	int	**fd;
	int	i;

	fd = NULL;
	fd = ft_init_fd(fd, data->pipe);
	if (data->cmd->arg[0] != NULL)
		start_pipe(fd[0], data);
	data->cmd = data->cmd->next;
	i = 0;
	while (++i && data->cmd->next != NULL)
	{
		if (data->cmd->arg[0] == NULL)
		{
			data->cmd = data->cmd->next;
			continue ;
		}
		child_process(data, fd, i - 1);
		data->cmd = data->cmd->next;
	}
	if (data->cmd->arg[0] != NULL)
		end_pipe(fd[i - 1], data);
	close(fd[0][0]);
	close(fd[i - 1][1]);
}
