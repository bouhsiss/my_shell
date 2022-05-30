/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:05:44 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/30 15:22:15 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*env_value(t_envlist **envlist, char *key)
{
	int			i;
	t_envlist	*env;

	i = 0;
	env = (*envlist);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		i++;
		env = env->next;
	}
	return (NULL);
}

t_envlist	*envlist_new(char *key, char *value)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof (t_envlist));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->sep = '=';
	new->next = NULL;
	return (new);
}

void	envlist_addback(t_envlist **env, t_envlist *new)
{
	t_envlist	*temp;

	temp = *env;
	if (!new)
		return ;
	new->next = NULL;
	if (!*env)
		*env = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
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
		envlist_addback(&envlist, envlist_new(key, value));
		free(temp);
		i++;
	}
	return (envlist);
}
