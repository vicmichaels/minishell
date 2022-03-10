/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:35:54 by esylva            #+#    #+#             */
/*   Updated: 2022/03/06 14:28:20 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_dir(t_data *data, char **sp_path)
{
	char	*ret;
	char	*tmp;
	int		i;

	tmp = NULL;
	ret = NULL;
	i = -1;
	while (sp_path[++i])
	{
		tmp = ft_strdup(sp_path[i]);
		ret = ft_strjoin_m(tmp, "/");
		tmp = ft_strjoin(ret, data->cmd->arg[0]);
		if (!tmp)
			return (NULL);
		if (!access(tmp, 0))
			break ;
		free(tmp);
		free(ret);
		ret = NULL;
		tmp = NULL;
	}
	free(tmp);
	return (ret);
}

char	*ft_take_path(t_data *data)
{
	char	*path;
	char	**sp_path;
	char	*ret;

	{
		path = find_value(data, "PATH");
		if (!path)
			return (NULL);
		sp_path = ft_split(path, ':');
		if (!sp_path)
			return (NULL);
		ret = ft_check_dir(data, sp_path);
		if (!ret)
			data->ret_val = 12;
	}
	return (ret);
}
