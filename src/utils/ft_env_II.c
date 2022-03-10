/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_II.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:51:22 by crobot            #+#    #+#             */
/*   Updated: 2022/03/06 14:13:21 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env(t_data *data)
{
	if (data->envar)
		data->envar = free_2d_arr(data->envar);
	data->envar = ft_new_envar(data->envar, data);
	if (!data->envar)
		ft_exit(data, 3);
	return (data->ret_val);
}

int	ft_cycle(t_env *tmp, char **arr, int i, t_data *data)
{
	while (tmp)
	{
		if (tmp->value)
		{
			arr[i] = ft_new_str_env(tmp);
			if (!arr[i])
			{
				data->ret_val = 12;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

int	ft_size_of_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*ft_new_str_env(t_env *env)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(env->key);
	if (!str)
		return (NULL);
	tmp = ft_strjoin_m(str, "=");
	if (!tmp)
		return (NULL);
	str = ft_strjoin_m(tmp, env->value);
	if (!str)
		return (NULL);
	return (str);
}

char	**ft_new_envar(char **arr, t_data *data)
{
	int		i;
	t_env	*tmp;

	i = ft_size_of_env(data->env);
	if (!i)
		return (NULL);
	arr = (char **)malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = data->env;
	i = ft_cycle(tmp, arr, i, data);
	arr[i] = NULL;
	return (arr);
}
