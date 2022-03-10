/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:09:04 by esylva            #+#    #+#             */
/*   Updated: 2022/03/06 14:27:31 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(t_data *data)
{
	t_env	*aa;

	aa = (t_env *)malloc(sizeof(t_env));
	if (!aa)
	{
		data->ret_val = 12;
		return (NULL);
	}
	aa->key = NULL;
	aa->value = NULL;
	aa->next = NULL;
	aa->prev = NULL;
	return (aa);
}

void	ft_lstadd_back(t_env *new, t_data *data, char *key, char *value)
{
	t_env	*elem;
	t_env	**lst;

	lst = &data->env;
	if (lst)
	{
		if (*lst)
		{
			elem = ft_lstlast(*lst);
			elem->next = new;
			new->prev = elem;
		}
		else
			*lst = new;
		new->key = ft_strdup(key);
		if (value)
			new->value = ft_strdup(value);
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstdelone(t_env *lst)
{
	if (lst)
	{
		free(lst->key);
		free(lst->value);
		if (lst->next)
			lst->next->prev = lst->prev;
		if (lst->prev)
			lst->prev->next = lst->next;
		free(lst);
	}
}

void	ft_lstclear(t_env **lst)
{
	t_env	*new_adr;

	if (!lst || !*lst)
		return ;
	while (lst && *lst)
	{
		new_adr = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = new_adr;
	}
}
