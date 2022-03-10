/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:56:34 by crobot            #+#    #+#             */
/*   Updated: 2022/02/09 20:06:07 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*ft_strjoin_m(char *memory, char *buffer)
{
	char		*new;
	int			i;
	int			j;
	int			new_len;

	new_len = ft_strlen(memory) + ft_strlen(buffer) + 1;
	new = malloc(sizeof(char) * new_len);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	new[new_len - 1] = '\0';
	new_len = 0;
	if (memory)
		while (memory[i] != '\0')
			new[new_len++] = memory[i++];
	if (buffer)
		while (buffer[j] != '\0')
			new[i++] = buffer[j++];
	free(memory);
	return (new);
}

int	ft_isnewline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*free_smth(char *str)
{
	free (str);
	return (NULL);
}
