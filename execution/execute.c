/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:13:15 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/16 17:41:55 by hbouhsis         ###   ########.fr       */
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
			count++;
		cmd_list->cmd = lowcase(cmd_list->cmd);
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

int openf_in(char *file)
{
	if (access(file, F_OK) == 0)
	{
		return(open(file, O_RDONLY));
	}
	else
	{
		dprintf(2, "no such file or directory: %s", file );
		exit(0);
	}
}

void cmd_exec(int fd_in, int *ends, t_parse *cmd_list)
{	
	int fd_out;
	if(cmd_list-> redirection != NULL && cmd_list->redirection->type == 1)
		fd_in = openf_in(cmd_list->redirection->file);
	dup2(fd_in, 0);
	
	if (cmd_list->next != NULL)
		dup2(ends[1], 1);
	if (cmd_list->redirection != NULL && cmd_list->redirection->type == 2)
	{
		fd_out = open(cmd_list->redirection->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_out, 1);
	}
	if (cmd_list->redirection != NULL && cmd_list->redirection->type == 4)
	{
		fd_out = open(cmd_list->redirection->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd_out, 1);
	}
	close(ends[0]);
	execvp(cmd_list->args[0], cmd_list->args);
}

void execute(char **env)
{
	int cmds_nbr;
	pid_t id;
	int ends[2];
	int fd_in = 0;
	t_parse *cmd_list;
	
	env = 0;
	cmds_nbr = count_and_lowcase();
	cmd_list = mini.command;
	while(cmds_nbr > 0)
	{
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
			cmd_exec(fd_in , ends, cmd_list);
		else
		{
			wait(0);
			close(ends[1]);
			fd_in = ends[0];
			cmds_nbr--;
			cmd_list = cmd_list->next;
		}
	}
}