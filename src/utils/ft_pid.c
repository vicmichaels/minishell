/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:47:51 by crobot            #+#    #+#             */
/*   Updated: 2022/02/15 18:47:53 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_signal_handler(int signo)
{
	(void)signo;
}

void	ft_add_pid(pid_t *pid, pid_t pid_value)
{
	int	i;

	i = 0;
	while (pid[i] != -1)
		i++;
	pid[i] = pid_value;
}

void	ft_wait_pid(t_data *data)
{
	int	i;

	i = 0;
	while (data->pid[i] != -1)
	{
		if (waitpid(data->pid[i], &data->ret_val, 0) == -1)
			return (perror("WAIT_PID"));
		if (WIFSIGNALED(data->ret_val))
			data->ret_val = 130;
		else
			data->ret_val = WEXITSTATUS(data->ret_val);
		i++;
	}
}
