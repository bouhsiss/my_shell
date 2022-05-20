/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:13:15 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/20 21:05:43 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *lowcase(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;	
	}
	return(str);
}

int count_and_lowcase()
{
	int count;
	t_parse *cmd_list;

	count = 0;
	cmd_list = mini.command;
	while(cmd_list)
	{
		if (cmd_list->cmd)
		{
			count++;
			cmd_list->cmd = lowcase(cmd_list->cmd);
		}
		cmd_list = cmd_list->next;
	}
	return(count);
}

char **bin_path(char **env)
{
	int i;
	char **path=NULL;
	
	i = 0;

	while(env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i], '=');
			path = ft_split(path[1], ':');
			return(path);
		}
		i++;
	}
	return(path);
}

t_parse *ignore_redr(t_parse *cmd_list)
{
	t_redirection *redr;
	
	if (cmd_list && cmd_list->cmd == NULL && cmd_list->redirection)
	{
		redr = cmd_list->redirection;
		if (redr->type == 2)
			open(redr->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (redr->type == 3)
			open_heredoc(name_generator(), redr->file, 0);
		if (redr->type == 4)
			open(redr->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		 cmd_list = cmd_list->next;
	}
	return(cmd_list);
}

void execute(char **env)
{
	int cmds_nbr;
	pid_t id;
	int ends[2];
	int fd_in = 0;
	int fd_out = 1;
	t_parse *cmd_list;
	
	env = 0;
	cmds_nbr = count_and_lowcase();
	cmd_list = mini.command;
	while(cmds_nbr > 0)
	{
		cmd_list = ignore_redr(cmd_list);
		if(pipe(ends) == -1)
		{
			perror("Pipe :");
			exit(1);
		}
		if ((id = fork()) == -1)
		{
			dprintf(2, "Error");
			exit(EXIT_FAILURE);
		}
		if (id == 0)
		{
			dupper(fd_in, ends, cmd_list, fd_out);
			close(ends[0]);
			if (execvp(cmd_list->args[0], cmd_list->args) == -1)
			{
				dprintf(2, "error\n");
				exit(0);
			}
		}
		else
		{
			wait(0);
			close(ends[1]);
			if (cmd_list->next != NULL)
				fd_in = ends[0];
			cmds_nbr--;
			cmd_list = cmd_list->next;
		}
	}
	cmd_list = ignore_redr(cmd_list);
}