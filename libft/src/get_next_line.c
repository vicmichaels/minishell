/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:56:26 by crobot            #+#    #+#             */
/*   Updated: 2022/01/13 14:48:28 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*ft_getline(char *memory)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!memory)
		return (0);
	while (memory[i] && memory[i] != '\n')
		i++;
	tmp = malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (memory[i])
	{
		if (memory[i] == '\n')
		{
			tmp[i] = '\n';
			tmp[i + 1] = '\0';
			return (tmp);
		}
		tmp[i] = memory[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_freememory(char *memory)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!memory)
		return (NULL);
	while (memory[i] && memory[i] != '\n')
		i++;
	if (!memory[i])
	{
		free(memory);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * ((ft_strlen(memory) - i) + 1));
	if (!tmp)
		return (NULL);
	i++;
	while (memory[i] && memory[i] != '\0')
		tmp[j++] = memory[i++];
	tmp[j] = '\0';
	free(memory);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char			*buf;
	static char		*memory;
	int				bytes_read;
	char			*line;

	bytes_read = 1;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_isnewline(memory) && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_smth(buf));
		buf[bytes_read] = '\0';
		memory = ft_strjoin_m(memory, buf);
	}
	free(buf);
	line = ft_getline(memory);
	memory = ft_freememory(memory);
	if (bytes_read == 0 && *line == '\0')
		return (free_smth(line));
	return (line);
}
