/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:04:45 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/29 15:55:18 by hbouhsis         ###   ########.fr       */
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
		exit(1);
	}
	chdir(home_path);
	return (EXIT_SUCCESS);
}

int	cd_builtin(char **args, t_envlist *env)
{
	if (!args[1])
		cd_home(env);
	else
		chdir(args[1]);
	return (EXIT_SUCCESS);
}
