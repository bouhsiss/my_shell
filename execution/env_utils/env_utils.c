/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:05:44 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/31 13:17:52 by hbouhsis         ###   ########.fr       */
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

int	check_key(char *arg, char *key)
{
	int	i;

	i = 0;
	if (char_isdigit(key) == 0 || (key[0] >= '0' && key[0] <= '9'))
	{
		error_message(key, "not a valid identifier");
		g_mini.exit_code = 1;
		return (0);
	}
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	g_mini.exit_code = 0;
	return (0);
}
