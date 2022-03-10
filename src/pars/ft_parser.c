/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:37:19 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 11:37:21 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_symbol_handler(t_data *data, char **line, int *i, int *j)
{
	int	flag;

	flag = FALSE;
	if ((line[0][*i] == 9 || line[0][*i] == 32) && (*i == *j))
		*j = ft_space_skipper(*line, i);
	if (line[0][*i] == '\'' || line[0][*i] == '\"')
		flag = TRUE;
	if (line[0][*i] == '\'')
		*line = ft_quote_handler(*line, i);
	else if (line[0][*i] == '\"')
		*line = ft_2quotes_handler(*line, i, data->envar, data->status);
	else if (line[0][*i] == '$')
		*line = ft_dollar_handler(*line, i, data->envar, data->status);
	if (!(*line))
		data->ret_val = ER_MALLOC;
	return (flag);
}

int	ft_parser_util(t_data *data, char **line, int *i, int *j)
{
	int	flag;

	flag = FALSE;
	if (line[0][*i] == '\0' && (*i == *j))
	{
		(*i)++;
		return (flag);
	}
	if (ft_special_symbol(line[0][*i], *i, *j) == TRUE)
		flag = ft_symbol_handler(data, line, i, j);
	else if (line[0][*i] == 9 || line[0][*i] == 32 || line[0][*i] == '\0')
		ft_get_com_args(data, *line, i, j);
	else if (line[0][*i] == '|')
		ft_pipe_handler(data, *line, i, j);
	else if ((line[0][*i] == '>' || line[0][*i] == '<'))
		ft_redir_handler(data, line, i, j);
	else
		(*i)++;
	return (flag);
}

int	ft_get_com_args(t_data *data, char *line, int *i, int *j)
{
	char	*string;
	char	**arg;

	string = ft_substr(line, *j, *i - *j);
	if (!string)
		return (data->ret_val = ER_MALLOC);
	arg = ft_arr_plus(data->cmd->arg, string);
	if (!arg)
		return (data->ret_val = ER_MALLOC);
	if (data->cmd->arg)
		free(data->cmd->arg);
	data->cmd->arg = arg;
	data->cmd->arg_num++;
	*j = ft_space_skipper(line, i);
	return (OK);
}

int	ft_pipe_exist(char *line, int *i, int *j)
{
	while (line[*i] != '|' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '|')
		*j = *i;
	else
		return (1);
	return (0);
}

int	ft_parser(t_data *data, char **line)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	if (ft_preparser(data, *line))
		return (ER_PREPARSER);
	while (1)
	{
		flag = ft_parser_util(data, line, &i, &j);
		if (data->ret_val != OK && ft_pipe_exist(*line, &i, &j))
			return (ERROR);
		if (line[0][i - 1] == '\0')
			return (OK);
		if (flag == TRUE && ft_is_empty(line[0][i]) == TRUE)
			ft_get_com_args(data, *line, &i, &j);
		if (data->ret_val != OK && ft_pipe_exist(*line, &i, &j))
			return (ERROR);
		if (flag == TRUE && line[0][i] == '\0')
			return (OK);
	}
	return (ERROR);
}
