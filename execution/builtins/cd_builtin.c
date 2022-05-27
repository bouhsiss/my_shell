/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:04:45 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/27 19:14:33 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	cd_home(t_envlist *env)
{
	char	*home_path;

	home_path = env_value(&env, "HOME=");
	chdir(home_path);
}

int	cd_builtin(char **args, t_envlist *env)
{
	if (!args[1])
		cd_home(env);
	else
		chdir(args[1]);
	return (EXIT_SUCCESS);
}
