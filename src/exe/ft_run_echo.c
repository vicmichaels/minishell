/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:56:55 by esylva            #+#    #+#             */
/*   Updated: 2022/02/18 20:06:32 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str, "-n"))
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_run_echo(t_data *data)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (data->cmd->arg[i] && ft_check_n(data->cmd->arg[i]))
	{
		i++;
		n = 1;
	}
	while (data->cmd->arg[i])
	{
		write(data->cmd->fd_out, data->cmd->arg[i],
			ft_strlen(data->cmd->arg[i]));
		data->ret_val = errno;
		if (data->ret_val)
			return ;
		if (i < data->cmd->arg_num - 1)
			write(data->cmd->fd_out, " ", 1);
		i++;
	}
	if (!n)
		write(data->cmd->fd_out, "\n", 1);
}
