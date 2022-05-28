/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:53:58 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/28 12:16:55 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	ac = 0;
	av = 0;
	while (1)
	{
		free_all();
		catch_signal();
		g_mini.envlist = env_builder(env);
		g_mini.line = readline("MINISHELL 🥵:");
		if (g_mini.line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (g_mini.line[0] == '\0')
			continue ;
		add_history(g_mini.line);	
		parse();
		t_parse *cmd_list;
		cmd_list = g_mini.command;
		if (ft_strcmp(cmd_list->cmd, "export") == 0)
			export_builtin(cmd_list);
		else
		{
			implement_heredoc();
			pipeline_execution(env);
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