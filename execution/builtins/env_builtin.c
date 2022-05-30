/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:05:58 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/30 15:49:56 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	env_builtin(void)
{
	t_envlist	*env;

	env = g_mini.envlist;
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd(env->sep, 1);
		if (env->value == NULL)
			write(1, "\n", 1);
		else
			ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	g_mini.exit_code = 0;
	return (g_mini.exit_code);
}
