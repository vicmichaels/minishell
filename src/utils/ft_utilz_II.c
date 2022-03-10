/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilz_II.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:20:01 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 18:43:20 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ts	ft_write_ts(char *line, int *i, int j)
{
	t_ts	ts;

	ts.s1 = ft_substr(line, 0, j);
	ts.s2 = ft_substr(line, j + 1, *i - j - 1);
	ts.s3 = ft_strdup(line + *i);
	ts.s4 = NULL;
	return (ts);
}

void	ft_3sfd(char *s1, char *s2, char *s3, int fd)
{
	char	*tmp;

	tmp = ft_strjoin(ft_strjoin(s1, s2), s3);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

int	**malloc_2d_int(size_t size)
{
	int	**p;

	p = malloc(size);
	if (p == NULL)
		exit(1);
	return (p);
}

void	ft_cd_error(t_data *data)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(data->cmd->arg[1], 2);
	if (data->ret_val == 2)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (data->ret_val == 20)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (data->ret_val == 3)
		ft_putstr_fd(": HOME not set\n", 2);
	else if (data->ret_val == 4)
		ft_putstr_fd(": OLDPWD not set\n", 4);
	data->ret_val = 1;
}

int	cd_utils(t_data *data)
{
	if (!data->cmd->arg[1] || !ft_strncmp("~", data->cmd->arg[1], 1))
		ft_cd_home(data);
	else if (!ft_strcmp("-", data->cmd->arg[1]))
		ft_cd_oldpwd(data);
	if (data->ret_val)
		return (0);
	return (1);
}
