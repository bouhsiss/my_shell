/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:04:02 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/06/06 11:33:05 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	builtincheck(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	executebuiltin(t_parse *cmd_list, t_envlist **envlist)
{
	if (!ft_strcmp("echo", cmd_list->cmd))
		return (echo_builtin(cmd_list->args));
	if (!ft_strcmp("cd", cmd_list->cmd))
		return (cd_builtin(cmd_list->args, (*envlist)));
	if (!ft_strcmp("pwd", cmd_list->cmd))
		return (pwd_builtin());
	if (!ft_strcmp("export", cmd_list->cmd))
		return (export_builtin(cmd_list));
	if (!ft_strcmp("unset", cmd_list->cmd))
		return (unset_builtin(cmd_list));
	if (!ft_strcmp("env", cmd_list->cmd))
		return (env_builtin());
	if (!ft_strcmp("exit", cmd_list->cmd))
		return (exit_builtin(cmd_list));
	return (0);
}
