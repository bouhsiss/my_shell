/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:06:09 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/28 18:31:12 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void export_without_args(t_envlist *env)
{
	while(env)
	{
		if (!env->value)
			printf("declare -x %s%c\n", env->key, env->sep);
		else
			printf("declare -x %s%c%s\n", env->key, env->sep, env->value);
		env = env->next;
	}
}


int check_key(char *arg, char *key)
{
	int i;

	i = 0;
	if (char_isdigit(key) == 0 || (key[0] >= '0' && key[0] <= '9'))
	{
		error_message(key, "not a valid identifier");
		return(0);
	}
	while(arg[i])
	{
		if (arg[i] == '=')
			return(1);
		i++;
	}
	return(0);
}

int check_if_key_exist(t_envlist **env, char *key)
{
	t_envlist *env_temp;
	
	env_temp = (*env);
	while(env_temp)
	{
		if(ft_strcmp(env_temp->key, key) == 0)
			return(1);
		env_temp = env_temp->next;
	}
	return(0);
}

void replace_value(t_envlist **env, char *key, char *value)
{
	t_envlist *env_temp;

	env_temp = (*env);
	while(env_temp)
	{
		if (strcmp(key, env_temp->key) == 0)
		{
			env_temp->value = value;
			return ;
		}
		env_temp = env_temp->next;
	}
}

void export_with_args(t_envlist *env, char **args)
{
	int		i;
	char **temp;
	
	i = 1;
	temp = NULL;
	while(args[i])
	{
		temp = ft_split(args[i], '=');
		if (check_key(args[i], temp[0]))
		{
			if(check_if_key_exist(&env, temp[0]))
				replace_value(&env, temp[0], temp[1]);
			else
				envlist_addback(&g_mini.envlist, envlist_new(temp[0], temp[1]));
		}
		i++;
	}
}

int export_builtin(t_parse *cmd_list)
{
	t_envlist *env;

	env = g_mini.envlist;
	if (cmd_list->args[1] == NULL)
		export_without_args(env);
	else
		export_with_args(env, cmd_list->args);
	return (EXIT_SUCCESS);
}