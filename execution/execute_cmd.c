/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:22 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/06/06 11:46:52 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_paths(char *env_var, char *cmd)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(env_var, ':');
	if (path)
	{
		while (path[i])
		{
			path[i] = ft_strjoin2(path[i], "/");
			path[i] = ft_strjoin2(path[i], cmd);
			if (access(path[i], F_OK) == 0)
				return (path[i]);
			i++;
		}
	}
	return (NULL);
}

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

char	**envlist_to_envarr(t_envlist **envlist)
{
	char		**arr;
	int			i;
	t_envlist	*env;

	i = 0;
	env = (*envlist);
	arr = malloc((envlist_sz(envlist) + 1) * sizeof (char *));
	while (env)
	{
		arr[i] = join_3_strings(env->key, "=", env->value);
		i++;
		env = env->next;
	}
	arr[i] = 0;
	return (arr);
}

int	launch_child(int fd_in, int *ends, t_parse *cmd_list, t_envlist **env)
{
	int	id;

	g_mini.flag = 1;
	id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup_ends(ends, fd_in);
		if (ends[WRITE_END] > 2)
			close(ends[WRITE_END]);
		redirection_helper(cmd_list);
		if (cmd_list->cmd && builtincheck(cmd_list->cmd))
			exit(executebuiltin(cmd_list, env));
		else
			execute_cmd(cmd_list, env);
	}
	return (0);
}

int	execute_cmd(t_parse *cmd_list, t_envlist **envlist)
{
	char	*path;
	char	**envp;

	envp = envlist_to_envarr(envlist);
	if (cmd_list->cmd)
	{
		if (cmd_list->cmd[0] == '.' || cmd_list->cmd[0] == '/')
		{
			path = cmd_list->cmd;
			if (opendir(path))
			{
				error_message(path, "is a directory");
				g_mini.exit_code = 126;
				exit(g_mini.exit_code);
			}
		}
		else
			path = ft_paths(env_value(envlist, "PATH"), cmd_list->cmd);
		if (execve(path, cmd_list->args, envp) == -1)
		{
			error_message(cmd_list->cmd, "");
			g_mini.exit_code = 127;
			exit(g_mini.exit_code);
		}
	}
	exit(g_mini.exit_code);
}
