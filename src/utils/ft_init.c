/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:10:53 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 12:10:54 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_pid(t_data *data)
{
	int	i;

	i = 0;
	data->pid = (pid_t *)malloc((data->pipe + 1) * sizeof(pid_t));
	while (i <= data->pipe)
	{
		data->pid[i] = -1;
		i++;
	}
}

t_cmd	*ft_cmd_init(void)
{
	t_cmd	*cmd_elem;

	cmd_elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_elem)
		return (NULL);
	cmd_elem->next = NULL;
	cmd_elem->fd_in = 0;
	cmd_elem->fd_out = 1;
	cmd_elem->arg_num = 0;
	cmd_elem->arg = NULL;
	cmd_elem->arg = (char **)malloc(sizeof(char **));
	if (!(cmd_elem->arg))
	{
		free(cmd_elem);
		return (NULL);
	}
	cmd_elem->arg[0] = NULL;
	return (cmd_elem);
}

t_env	*ft_init_env(t_data *data, char **env)
{
	t_env	*new;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		new = ft_lstnew(data);
		data->ret_val += ft_split_env(env[i], &key, &value);
		if (data->ret_val)
			return (NULL);
		ft_lstadd_back(new, data, key, value);
		ft_free_key_value(&key, &value);
		i++;
	}
	return (data->env);
}

int	**ft_init_fd(int **fd, int count_pipe)
{
	int	i;

	i = 0;
	fd = malloc_2d_int(sizeof(int *) * (count_pipe));
	while (i < count_pipe - 1)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
		{
			perror("ERROR PIPE");
			exit(1);
		}
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

void	ft_init(t_data *data, char **env)
{
	data->ret_val = 0;
	data->envar = NULL;
	data->cmd = NULL;
	data->pid = NULL;
	data->line = NULL;
	data->env = NULL;
	data->env = ft_init_env(data, env);
	if (data->ret_val)
		ft_exit(data, 1);
}
