/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:29:02 by esylva            #+#    #+#             */
/*   Updated: 2022/02/26 20:14:23 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_exit(t_data *data)
{
	if (data->cmd->arg[1] && data->cmd->arg[2])
	{
		ft_printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->ret_val = 1;
	}
	if (data->cmd->arg[1] && ft_isall_digits(data->cmd->arg[1]))
	{
		data->ret_val = ft_atol(data->cmd->arg[1]) % 256;
		ft_exit(data, 1);
	}
	else if (data->cmd->arg[1])
	{
		ft_printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->cmd->arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->ret_val = 2;
		ft_exit(data, 2);
	}
	else
		ft_exit(data, 1);
}

void	ft_exit(t_data *data, int i)
{
	int	a;

	if (i == 0)
		ft_printf("\033[1A%sexit\n", data->line);
	else if (i == 1 && data->ret_val != 3 && data->ret_val != 258
		&& data->ret_val != 259)
		ft_printf("exit\n");
	else if (i == 3 || data->ret_val == 3)
		ft_printf("minishell: malloc error\n");
	else if (data->ret_val == 258 || data->ret_val == 259)
		ft_printf("minishell: syntax error\n");
	a = data->ret_val;
	ft_free_at_exit(data);
	exit(a);
}
