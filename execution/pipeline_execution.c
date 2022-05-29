/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:47 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/29 17:50:27 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	exec_last_cmd(t_parse *cmd_list, int fd_in, int *ends, t_envlist **env)
{
	pid_t	id;

	if (fd_in == 0)
	{
		if(builtincheck(cmd_list->cmd))
			return(executebuiltin(cmd_list, env));
	}
	id = fork();
	if (id == 0)
	{
		if (fd_in != STDIN_FILENO)
			dupfd2fd(fd_in, STDIN_FILENO);
		if (ends[WRITE_END] > 2)
			close(ends[WRITE_END]); 
		redirection_helper(cmd_list);
		if (builtincheck(cmd_list->cmd))
			exit(executebuiltin(cmd_list, env));
		else
			execute_cmd(cmd_list, env);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	return(0);
}

void	checker(void)
{
	t_parse	*cmd_list;

	cmd_list = g_mini.command;
	while (cmd_list)
	{
		cmd_list->cmd = lowcase(cmd_list->cmd);
		cmd_list = cmd_list->next;
	}
}

void	parent_process(void)
{
	int	exit_code;
	int	stat_loc;

	while (waitpid(-1, &stat_loc, 0) > 0)
	{
		if (WIFEXITED(stat_loc))
			exit_code = WEXITSTATUS(stat_loc);
	}
	printf("\n------\nparent returned -> exit_code = %d\n------\n", exit_code);
	while (wait(0) > 0)
		;
}

void	pipeline_execution(t_envlist **envlist)
{
	int		ends[2];
	t_parse	*cmd_list;
	int		fd_in;

	fd_in = STDIN_FILENO;
	checker();
	cmd_list = g_mini.command;
	while (cmd_list->next)
	{
		pipe(ends);
		launch_child(fd_in, ends, cmd_list, envlist);
		close_ends(ends, fd_in);
		fd_in = ends[READ_END];
		cmd_list = cmd_list->next;
	}
	exec_last_cmd(cmd_list, fd_in, ends, envlist);
	parent_process();
}
