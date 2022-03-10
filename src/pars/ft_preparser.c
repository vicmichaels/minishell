/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:41:36 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 11:41:37 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_scan_pipe(t_data *data, char *line, int start, int finish)
{
	while (start <= finish)
	{
		if (line[start] == '|' || line[start] == '\0' || line[start] == '\n')
		{
			data->ret_val = ER_SYNTAX;
			printf(W_SYNTAX);
			return (FALSE);
		}
		if (line[start] != 9 && line[start] != 32)
			return (TRUE);
		start++;
	}
	data->ret_val = ER_SYNTAX;
	printf(RED W_SYNTAX RESET);
	return (FALSE);
}

int	ft_check_pipe(t_data *data, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (ft_scan_pipe(data, line, j, i) == FALSE)
				return (ERROR);
			i++;
			if (line[i] == '|')
				i++;
			if (ft_scan_pipe(data, line, i, ft_strlen(line)) == FALSE)
				return (ERROR);
			j = i;
		}
		i++;
	}
	return (OK);
}

char	*ft_check_quotes(t_data *data, char *line)
{
	char	c;

	c = *line;
	line++;
	while (*line != c)
	{
		if (!(*line))
		{
			data->ret_val = ER_SYNTAX;
			printf(W_SYNTAX);
			return (NULL);
		}
		line++;
	}
	line++;
	return (line);
}

char	*ft_check_redirect(t_data *data, char *line)
{
	int		i;

	i = 0;
	if (*line == *(line + 1))
		line++;
	line++;
	while (1)
	{
		if (line[i] == '\n' || line[i] == '|' || line[i] == '<'
			|| line[i] == '>' || (!line[i]))
		{
			data->ret_val = ER_SYNTAX;
			printf(W_SYNTAX);
			return (NULL);
		}
		if (line[i] != 9 && line[i] != 32)
			return (line);
		i++;
	}
	return (line);
}

int	ft_preparser(t_data *data, char *line)
{
	data->pid = NULL;
	data->status = data->ret_val;
	data->ret_val = 0;
	data->cmd = ft_cmd_init();
	if (!data->cmd)
	{
		data->ret_val = ER_MALLOC;
		return (ERROR);
	}
	data->first_cmd = data->cmd;
	data->pipe = 1;
	if (ft_check_pipe(data, line) == ERROR)
		return (ERROR);
	while (*line)
	{
		if (*line == '\"' || *line == '\'')
			line = ft_check_quotes(data, line);
		else if ((*line == '>' || *line == '<'))
			line = ft_check_redirect(data, line);
		if (data->ret_val != OK)
			return (ERROR);
		line++;
	}
	return (OK);
}
