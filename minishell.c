/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:53:58 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/31 13:04:42 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(void)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(g_mini.exit_code);
}

int	main(int ac, char **av, char **env)
{
	ac = 0;
	av = 0;
	g_mini.envlist = env_builder(env);
	while (1)
	{
		free_all();
		catch_signal();
		g_mini.line = readline("UnToutPetitShell👼 :");
		if (g_mini.line == NULL)
			exit_shell();
		if (g_mini.line[0] == '\0')
			continue ;
		add_history(g_mini.line);
		parse();
		if (!g_mini.l_err && g_mini.command)
		{
			implement_heredoc();
			pipeline_execution(&g_mini.envlist);
			unlink_heredocs();
		}
	}
}
