/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:06:23 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 19:55:35 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, int err_num)
{
	data->ret_val = 1;
	if (err_num == 2 || err_num == 14)
	{
		ft_3sfd("minishell: ", data->cmd->arg[0],
			": command not found\n", 2);
		data->ret_val = 127;
	}
	else if (err_num == 13)
	{
		ft_3sfd("minishell: ", data->cmd->arg[0],
			": Permission denied\n", 2);
		data->ret_val = 126;
	}
	else if (err_num == 0)
	{
		ft_3sfd("minishell: ", data->cmd->arg[0], ": '", 2);
		ft_3sfd(data->cmd->arg[1], "': not a valid identifier\n",
			NULL, 2);
	}
	else
		perror(data->cmd->arg[0]);
}

void	minishell(t_data *data)
{
	char	*line;

	line = ft_put_prompt(data);
	if (line == NULL)
		ft_exit(data, 0);
	if (!(*line))
		return (free(line));
	add_history(line);
	data->ret_val = ft_parser(data, &line);
	data->cmd = data->first_cmd;
	if (!data->ret_val)
	{
		ft_init_pid(data);
		ft_execute(data);
		ft_wait_pid(data);
	}
	ft_free_at_exit(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		exit(127);
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_handler);
	ft_init(&data, env);
	data.envar = ft_log_env(ac, av, env);
	rl_outstream = stderr;
	while (1)
		minishell(&data);
	return (0);
}
