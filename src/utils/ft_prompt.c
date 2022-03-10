/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:40:30 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 12:40:32 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_dir(t_data *data)
{
	char	*dir;
	char	*tmp;
	char	*ret;
	size_t	len;

	tmp = NULL;
	dir = NULL;
	ret = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
		ft_exit(data, 1);
	tmp = ft_strrchr(dir, '/');
	if (!tmp)
		ft_exit(data, 1);
	len = ft_strlen(tmp + 1);
	ret = ft_substr(tmp, 1, len);
	free(dir);
	return (ret);
}

char	**ft_log_env(int ac, char **av, char **env)
{
	char		**log;
	size_t		i;

	i = 0;
	(void) ac;
	(void) av;
	log = malloc(sizeof(char *) * (len_2d_arr(env) + 1));
	while (i < len_2d_arr(env))
	{
		log[i] = ft_strdup(env[i]);
		i++;
	}
	log[i] = NULL;
	return (log);
}

char	*ft_get_env(char *prm, char **env)
{
	char	**tmp;
	char	*line;
	int		i;

	if (prm == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_split(env[i], '=');
		if (ft_strncmp(prm, tmp[0], ft_strlen(prm) + 1) == 0)
		{
			line = ft_strdup(tmp[1]);
			tmp = free_2d_arr(tmp);
			return (line);
		}
		i++;
		tmp = free_2d_arr(tmp);
	}
	return (NULL);
}

char	*ft_put_prompt(t_data *data)
{
	char	*user;
	char	*dir;
	char	*hued;
	char	*prompt;

	signal(SIGINT, signal_handler);
	user = ft_get_env("USER", data->envar);
	user = ft_strjoin_m(user, "@");
	dir = ft_get_dir(data);
	hued = ft_strjoin_m(user, dir);
	user = ft_strjoin(GREEN, hued);
	free(hued);
	hued = ft_strjoin_m(user, WHITE);
	hued = ft_strjoin_m(hued, " ");
	data->line = ft_strdup(hued);
	prompt = readline(hued);
	free(hued);
	free(dir);
	return (prompt);
}
