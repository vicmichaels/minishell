/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:57:45 by esylva            #+#    #+#             */
/*   Updated: 2022/02/26 23:48:35 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_built_in(t_data *data)
{
	if (!ft_strcmp("echo", data->cmd->arg[0]))
		ft_run_echo(data);
	else if (!ft_strcmp("cd", data->cmd->arg[0]))
		ft_run_cd(data);
	else if (!ft_strcmp("pwd", data->cmd->arg[0]))
		ft_run_pwd(data);
	else if (!ft_strcmp("export", data->cmd->arg[0]))
		ft_run_export(data);
	else if (!ft_strcmp("unset", data->cmd->arg[0]))
		ft_run_unset(data);
	else if (!ft_strcmp("env", data->cmd->arg[0]))
		ft_run_env(data);
	else if (!ft_strcmp("exit", data->cmd->arg[0]))
		ft_run_exit(data);
	else
		return (0);
	return (1);
}

void	ft_exec_bin(t_data *data)
{
	char	*path;

	if (data->cmd->arg[0] == NULL)
		return (exit(data->ret_val));
	path = ft_take_path(data);
	path = ft_strjoin_m(path, data->cmd->arg[0]);
	execve(path, data->cmd->arg, data->envar);
	ft_error(data, errno);
	exit(data->ret_val);
}

void	ft_exec_pipe(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_error(data, errno));
	else if (pid != 0)
		signal(SIGINT, child_signal_handler);
	ft_add_pid(data->pid, pid);
	if (pid == 0)
	{
		ft_redir_pipe(data);
		ft_exec_built_in(data);
		ft_exec_bin(data);
	}
}

void	ft_execute(t_data *data)
{
	pid_t	pid;

	if (data->pipe == 1)
	{
		if (data->cmd->arg[0] == NULL)
			return ;
		if (ft_exec_built_in(data))
			return ;
		pid = fork();
		if (pid == -1)
			return (ft_error(data, errno));
		else if (pid != 0)
			signal(SIGINT, child_signal_handler);
		ft_add_pid(data->pid, pid);
		if (pid == 0)
		{
			ft_redir_pipe(data);
			ft_exec_bin(data);
		}
		return ;
	}
	ft_pipe_work(data);
}
