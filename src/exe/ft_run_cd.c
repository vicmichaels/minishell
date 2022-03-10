/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:29:02 by esylva            #+#    #+#             */
/*   Updated: 2022/03/09 19:06:36 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_cd(t_data *data)
{
	char	*tmp_val;

	tmp_val = NULL;
	if (!cd_utils(data))
		return ;
	tmp_val = getcwd(tmp_val, 0);
	chdir(data->cmd->arg[1]);
	data->ret_val = errno;
	if (data->ret_val)
	{
		ft_cd_error(data);
		free (tmp_val);
		return ;
	}
	ft_oldpwd(data, tmp_val);
	free(tmp_val);
	ft_update_env(data);
}

void	ft_cd_oldpwd(t_data *data)
{
	char	*val;

	val = NULL;
	free(data->cmd->arg[1]);
	data->cmd->arg[1] = NULL;
	val = find_value(data, "OLDPWD");
	if (!val)
	{
		data->ret_val = 4;
		ft_cd_error(data);
		return ;
	}
	data->cmd->arg[1] = ft_strdup(val);
	if (!data->cmd->arg[1])
		data->ret_val = 12;
	else
		ft_printf("%s\n", data->cmd->arg[1]);
}

void	ft_oldpwd(t_data *data, char *tmp_val)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = find_env(data, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(tmp_val);
	}
	tmp = find_env(data, "PWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = NULL;
		tmp->value = getcwd(tmp->value, 0);
	}
	return ;
}

void	ft_cd_home(t_data *data)
{
	char	*val;
	char	**tmp;

	val = NULL;
	val = find_value(data, "HOME");
	if (!val)
	{
		data->ret_val = 3;
		ft_cd_error(data);
		return ;
	}
	if (data->cmd->arg[1])
		ft_chk_arg(data, val);
	else
	{
		tmp = data->cmd->arg;
		data->cmd->arg = ft_arr_plus(tmp, NULL);
		free(tmp);
		data->cmd->arg[1] = ft_strdup(val);
	}
}

void	ft_chk_arg(t_data *data, char *val)
{
	char	*str;

	str = NULL;
	str = ft_strdup(data->cmd->arg[1]);
	free(data->cmd->arg[1]);
	data->cmd->arg[1] = ft_strjoin(val, str + 1);
	free(str);
}
