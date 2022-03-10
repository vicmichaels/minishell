/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:30:29 by esylva            #+#    #+#             */
/*   Updated: 2022/02/02 19:10:17 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_unset(t_data *data)
{
	t_env	*first;
	int		i;

	first = data->env;
	i = 1;
	while (data->cmd->arg[i])
	{
		if (ft_iskey(data->cmd->arg[i], data))
			return ;
		while (data->env && (ft_strcmp(data->cmd->arg[i], data->env->key)))
			data->env = data->env->next;
		if (data->env)
			ft_lstdelone(data->env);
		data->env = first;
		i++;
	}
	ft_update_env(data);
}
