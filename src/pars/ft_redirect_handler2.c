/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_handler2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:05:58 by crobot            #+#    #+#             */
/*   Updated: 2022/02/24 12:06:00 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_redirect_out(t_data *data, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		data->ret_val = ER_FILE_OPEN;
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (ERROR);
	}
	if (data->cmd->fd_out != 1)
		close (data->cmd->fd_out);
	data->cmd->fd_out = fd;
	return (OK);
}

int	ft_redirect_out_append(t_data *data, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		data->ret_val = ER_FILE_OPEN;
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (ERROR);
	}
	if (data->cmd->fd_out != 1)
		close (data->cmd->fd_out);
	data->cmd->fd_out = fd;
	return (OK);
}

int	ft_redirect_in(t_data *data, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
	{
		data->ret_val = ER_FILE_OPEN;
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (ERROR);
	}
	if (data->cmd->fd_in != 0)
		close (data->cmd->fd_in);
	data->cmd->fd_in = fd;
	return (OK);
}
