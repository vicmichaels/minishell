/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:24:21 by esylva            #+#    #+#             */
/*   Updated: 2022/03/06 14:23:24 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_env(t_data *data)
{
	int	i;

	if (data->cmd->arg[1])
	{
		ft_env_error(data);
		return ;
	}
	i = -1;
	while (data->envar[++i])
	{
		if (wr_fd(data->cmd->fd_out, data->envar[i],
				ft_strlen(data->envar[i]), data))
			return ;
		if (wr_fd(data->cmd->fd_out, "\n", 1, data))
			return ;
	}
}

int	wr_fd(int fd, char *str, int len, t_data *data)
{
	if (len)
	{
		write(fd, str, len);
		data->ret_val = errno;
	}
	return (data->ret_val);
}

void	ft_env_error(t_data *data)
{
	data->ret_val = 127;
	ft_putstr_fd("env: \'", 2);
	ft_putstr_fd(data->cmd->arg[1], 2);
	ft_putstr_fd("\': No such file or directory\n", 2);
}
