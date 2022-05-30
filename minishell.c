/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:53:58 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/30 22:57:37 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_shell(void)
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
		if(g_mini.l_err == 0)
		{
			implement_heredoc();
			pipeline_execution(&g_mini.envlist);
			unlink_heredocs();
		}
	}
}


// printing loop

// 		t_parse *cmd_list=mini.command;
// 		int i = 0;
// 		while(cmd_list)
// 		{
// 			printf("cmd == %s\n", cmd_list->cmd);
// 			printf("====================\n");
// 			i = 0;
// 			while(cmd_list->args[i])
// 			{
// 				printf("args[%d] == %s\n", i, cmd_list->args[i]);
// 				i++;
// 			}
// 			printf("======================\n");
// 			printf("argsc == %d\n", cmd_list->argsc);
// 			printf("======================\n");
// 			while(cmd_list->redirection)
// 			{
// 				printf("redirection->type %d\n", cmd_list->redirection->type);
// 				printf("redirection->file %s\n", cmd_list->redirection->file);
// 				printf("redirection->fd %d\n", cmd_list->redirection->fd);
// 				cmd_list->redirection = cmd_list->redirection->next;
// 			}
// 			printf("\n***********************************************\n");
// 			cmd_list= cmd_list->next;
// 		}
