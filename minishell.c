/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:53:58 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/11 20:26:39 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	ac = 0;
	av = 0;
	env = 0;
	int i;
	t_parse *cmd_list;

	while (1)
	{
		mini.line = readline("MINISHELL 🥵:");
		if (mini.line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		if (mini.line == '\0')
			continue ;
		add_history(mini.line);
		parse();
		cmd_list = mini.command;
		while(cmd_list)
		{
			printf("cmd == %s\n", cmd_list->cmd);
			printf("====================\n");
			i = 0;
			while(cmd_list->args[i])
			{
				printf("args[%d] == %s\n", i, cmd_list->args[i]);
				i++;
			}
			printf("======================\n");
			printf("argsc == %d\n", cmd_list->argsc);
			printf("======================\n");
			if (cmd_list->redirection == 0)
				printf("had lqlawi khawi\n");
			while(cmd_list->redirection)
			{
				printf("ana hna azebi\n");
				printf("redirection->type %d\n", cmd_list->redirection->type);
				printf("redirection->file %s\n", cmd_list->redirection->file);
				printf("redirection->fd %d\n", cmd_list->redirection->fd);
				cmd_list->redirection = cmd_list->redirection->next;
			}
			printf("\n***********************************************\n");
			cmd_list= cmd_list->next;
		}
		// execute(env);
	}
}


// printing loop
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