/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:05:37 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/31 11:27:23 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	isoption(char *arg)
{
	int	i;

	i = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	echo_with_option(char **args)
{
	int	i;

	i = 2;
	if (!args[i])
		return ;
	while (isoption(args[i]))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

void	echo_without_option(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

int	echo_builtin(char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_mini.exit_code = 0;
		return (g_mini.exit_code);
	}
	else
	{
		if (isoption(args[1]))
			echo_with_option(args);
		else
		{
			echo_without_option(args);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	g_mini.exit_code = 0;
	return (g_mini.exit_code);
}
