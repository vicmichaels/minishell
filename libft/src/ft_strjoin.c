/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:52:32 by crobot            #+#    #+#             */
/*   Updated: 2021/11/26 13:52:34 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;
	size_t	new_len;

	if (!s1 || !s2)
		return (NULL);
	new_len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * (new_len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	new_len = 0;
	while (s1[i])
		new[new_len++] = s1[i++];
	while (s2[j])
		new[new_len++] = s2[j++];
	new[new_len] = '\0';
	return (new);
}
