/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:18:41 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/31 13:33:43 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_signals(int i)
{
	(void)i;
	if (!g_mini.flag)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	catch_signal(void)
{
	signal(SIGINT, ft_signals);
	signal(SIGQUIT, SIG_IGN);
}
