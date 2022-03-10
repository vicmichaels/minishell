/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:00:42 by crobot            #+#    #+#             */
/*   Updated: 2022/02/24 12:00:43 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_redir_arg(char *arg)
{
	while (1)
	{
		if (*arg == '\0' || *arg == '\n')
			return (FALSE);
		if (*arg != '>' && *arg != '<' && *arg != '|')
			return (TRUE);
		arg++;
	}
	return (FALSE);
}

int	ft_redir_opener(t_data *data, char *redir_arg, int empty_flag)
{
	int	status;

	if (ft_check_redir_arg(redir_arg) == FALSE && empty_flag != 0)
	{
		data->ret_val = ER_SYNTAX;
		printf(W_SYNTAX);
		return (ERROR);
	}
	if (data->cmd->redir_flag == R_OUT)
		status = ft_redirect_out(data, redir_arg);
	if (data->cmd->redir_flag == R_OUT_APPEND)
		status = ft_redirect_out_append(data, redir_arg);
	if (data->cmd->redir_flag == R_IN)
		status = ft_redirect_in(data, redir_arg);
	if (data->cmd->redir_flag == R_HEREDOC)
		status = ft_heredoc(data, redir_arg);
	data->cmd->redir_flag = R_FALSE;
	return (status);
}

int	ft_redir_finder(int *redir_flag, char *line, int *i)
{
	if (line[*i] == '>')
	{
		(*i)++;
		*redir_flag = R_OUT;
		if (line[*i] == '>')
		{
			(*i)++;
			*redir_flag = R_OUT_APPEND;
		}
	}
	else if (line[*i] == '<')
	{
		(*i)++;
		*redir_flag = R_IN;
		if (line[*i] == '<')
		{
			(*i)++;
			*redir_flag = R_HEREDOC;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

char	*ft_redir_symbol(t_data *data, char *line, int *i)
{
	while (line[*i] != 9 && line[*i] != 32 && line[*i] != '\0'
		&& line[*i] != '>' && line[*i] != '<' && line[*i] != '|')
	{
		if (line[*i] == '\'')
			line = ft_quote_handler(line, i);
		else if (line[*i] == '\"')
			line = ft_2quotes_handler(line, i, data->envar, data->ret_val);
		else if (line[*i] == '$')
			line = ft_dollar_handler(line, i, data->envar, data->ret_val);
		else
			(*i)++;
	}
	return (line);
}

void	ft_redir_handler(t_data *data, char **line, int *i, int *j)
{
	char	*tmp;
	int		status;

	if (*i != *j && ft_get_com_args(data, *line, i, j) != OK)
		return ;
	ft_redir_finder(&data->cmd->redir_flag, *line, i);
	ft_space_skipper(*line, i);
	*j = *i;
	*line = ft_redir_symbol(data, *line, i);
	if (!(*line))
		return ;
	tmp = ft_substr(*line, *j, *i - *j);
	if (!tmp)
	{
		data->ret_val = ER_MALLOC;
		return ;
	}
	status = ft_redir_opener(data, tmp, *i - *j);
	free (tmp);
	if (status != OK)
		return ;
	*j = *i;
}
