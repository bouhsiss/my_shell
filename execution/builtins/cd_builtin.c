/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:04:45 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/30 22:31:54 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	cd_home(t_envlist *env)
{
	char	*home_path;

	home_path = env_value(&env, "HOME");
	if (!home_path)
	{
		error_message("cd", "HOME not set");
		g_mini.exit_code = 1;
		return (g_mini.exit_code);
	}
	if (chdir(home_path) == 0)
		g_mini.exit_code = 0;
	else
	{
		error_message("cd", "");
		g_mini.exit_code = 1;
	}
	return (g_mini.exit_code);
}

int	cd_builtin(char **args, t_envlist *env)
{
	if (!args[1])
		g_mini.exit_code = cd_home(env);
	else if (chdir(args[1]) == 0)
		g_mini.exit_code = 0;
	else
	{
		error_message("cd", args[1]);
		g_mini.exit_code = 1;
	}
	return (g_mini.exit_code);
}
