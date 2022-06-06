/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:30:19 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/06/06 18:30:21 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	ext_child_process(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mini.exit_code = 1;
	}
	else if (signum == SIGQUIT)
	{
		ft_putchar_fd('\r', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_process(int signum)
{
	if (!kill(g_mini.id, signum))
	{
		if (signum == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_mini.exit_code = 131;
		}
		else if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_mini.exit_code = 130;
		}
	}
	else
		ext_child_process(signum);
}

void	ft_signals(int signum)
{
	if (g_mini.id != 0)
		child_process(signum);
	else
		ext_child_process(signum);
}

void	catch_signal(void)
{
	signal(SIGINT, ft_signals);
	signal(SIGQUIT, ft_signals);
}
