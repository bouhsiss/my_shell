/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:22 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/28 20:31:54 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_paths(char *env_var, char *cmd)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(env_var, ':');
	if(!path[i])
	{
		printf("UO");
		
	}
	while (path[i])
	{
		path[i] = ft_strjoin2(path[i], "/");
		path[i] = ft_strjoin2(path[i], cmd);
		if (access(path[i], F_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

int envlist_sz(t_envlist **envlist)
{
	int count;
	t_envlist *env;

	count = 0;
	env = (*envlist);
	while(env)
	{
		count++;
		env = env->next;
	}
	return(count);
}

char **envlist_to_envarr(t_envlist **envlist)
{
	char **arr;
	int i;
	t_envlist *env;
	
	i = 0;
	env = (*envlist);
	arr = malloc(envlist_sz(envlist) * sizeof(char *));
	while(env)
	{
		arr[i] = join_3_strings(env->key, "=", env->value);
		i++;
		env = env->next;
	}
	arr[i] = 0;
	return(arr);
}

int builtincheck(char *cmd)
{
	char *builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int i;
	
	i = 0;
	while(i<7)
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return(1);
		i++;
	}
	return(0);
}

int executebuiltin(t_parse *cmd_list, t_envlist **envlist)
{
	if (ft_strcmp("echo", cmd_list->cmd))
		return(echo_builtin(cmd_list->args));
	if (ft_strcmp("cd", cmd_list->cmd))
		return(cd_builtin(cmd_list->args, (*envlist)));
	if (ft_strcmp("pwd", cmd_list->cmd))
		return(pwd_builtin());
	if(ft_strcmp("export", cmd_list->cmd))
		return(export_builtin(cmd_list));
	if (ft_strcmp("unset", cmd_list->cmd))
		return(unset_builtin(cmd_list));
	if (ft_strcmp("env", cmd_list->cmd))
		return(env_builtin());
	return(88);
}

void	execute_cmd(t_parse *cmd_list,t_envlist **envlist)
{
	char	*path;
	char **envp;

	envp = envlist_to_envarr(envlist);
	if (cmd_list->cmd)
	{
		if (builtincheck(cmd_list->cmd))
			executebuiltin(cmd_list, envlist);
		else
		{
		path = ft_paths(env_value(envlist, "PATH"), cmd_list->cmd);
		if (execve(path, cmd_list->args, envp) == -1)
			exit(127);
		}
	}
	exit(99);
}
