/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:05:37 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/27 12:05:38 by hbouhsis         ###   ########.fr       */
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
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
}

int	echo_builtin(char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		ft_putstr_fd("\n", 1);
	else
	{
		if (isoption(args[1]))
			echo_with_option(args);
		else
		{
			while (args[i])
			{
				ft_putstr_fd(args[i], 1);
				i++;
				if (args[i] != NULL)
					ft_putstr_fd(" ", 1);
			}
			ft_putstr_fd("\n", 1);
		}
	}
	return (EXIT_SUCCESS);
}
