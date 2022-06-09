/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:17:57 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/06/06 18:38:21 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	envlist_sz(t_envlist **envlist)
{
	int			count;
	t_envlist	*env;

	count = 0;
	env = (*envlist);
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

t_envlist	*env_builder(char **env)
{
	char		*key;
	char		*value;
	int			i;
	t_envlist	*envlist;
	char		**temp;

	i = 0;
	envlist = g_mini.envlist;
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		key = temp[0];
		value = temp[1];
		envlist_addback(&envlist, envlist_new(key, '=', value));
		free(temp);
		i++;
	}
	return (envlist);
}
