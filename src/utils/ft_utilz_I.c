/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilz_I.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:41:52 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 12:41:54 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iskey(char *key, t_data *data)
{
	data->ret_val = 0;
	if (key)
	{
		if (key[0] == '_' || ft_isalpha(key[0]))
		{
			key++;
			while (*key)
			{
				if (*key == '_' || ft_isalnum(*key))
					key++;
			}
			return (0);
		}
	}
	data->ret_val = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->arg[0], 2);
	ft_putstr_fd(": \'", 2);
	ft_putstr_fd(data->cmd->arg[1], 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (1);
}

char	**ft_arr_plus(char **arr, char *str)
{
	char	**new_arr;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (arr[++i] != NULL)
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[len + 1] = NULL;
	new_arr[len] = NULL;
	i = -1;
	while (arr[++i] != NULL)
		new_arr[i] = arr[i];
	new_arr[i] = str;
	return (new_arr);
}

size_t	len_2d_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i] != NULL)
		i++;
	return (i);
}

int	ft_isall_digits(char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		i++;
	while (*(str + i))
	{
		if (!ft_isdigit((unsigned char)*(str + i) || ft_strlen(str) >= 19))
			return (1);
	}
	return (0);
}

long	ft_atol(char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
