/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:22:49 by esylva            #+#    #+#             */
/*   Updated: 2022/03/06 14:26:24 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_pwd(t_data *data)
{
	char	*p;

	p = NULL;
	p = getcwd(p, 0);
	write(data->cmd->fd_out, p, ft_strlen(p));
	data->ret_val = errno;
	if (data->ret_val)
	{
		free(p);
		p = NULL;
		return ;
	}
	write(data->cmd->fd_out, "\n", 1);
	data->ret_val = errno;
	free(p);
	p = NULL;
}
