/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_handler3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:51:11 by crobot            #+#    #+#             */
/*   Updated: 2022/03/10 18:33:34 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_rewrite_strnstr(char *stop_word, char *text)
{
	int	i;
	int	k_len;
	int	s_len;

	i = 0;
	k_len = ft_strlen(stop_word);
	s_len = ft_strlen(text);
	while (i < k_len && i < s_len)
	{
		if (stop_word[i] != text[i])
			return (FALSE);
		i++;
	}
	if (stop_word[i] == text[i])
		return (TRUE);
	return (FALSE);
}

void	ft_put_in_fd(int fd, char *stop_word)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (*line == '\0')
			rl_redisplay();
		if (ft_rewrite_strnstr(stop_word, line) == TRUE)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		rl_on_new_line();
	}
}

int	ft_heredoc(t_data *data, char *stop_word)
{
	int		fd;

	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		data->ret_val = ER_FILE_OPEN;
		ft_putstr_fd("heredoc", 2);
		ft_putstr_fd("> ", 2);
		return (ERROR);
	}
	ft_put_in_fd(fd, stop_word);
	close(fd);
	fd = open("heredoc", O_RDONLY, 0644);
	if (data->cmd->fd_in != 0)
		close (data->cmd->fd_in);
	data->cmd->fd_in = fd;
	if (!access("heredoc", 0))
		unlink("heredoc");
	return (OK);
}
