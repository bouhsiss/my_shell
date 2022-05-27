/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:47 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/26 17:21:02 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	exec_last_cmd(t_parse *cmd_list, int fd_in, int *ends, char **env)
{
	pid_t	id;

	id = fork();
	if (id == 0)
	{
		if (fd_in != STDIN_FILENO)
			dupfd2fd(fd_in, STDIN_FILENO);
		if (ends[WRITE_END] > 2)
			close(ends[WRITE_END]);
		redirection_helper(cmd_list);
		execute_cmd(cmd_list, env);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
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

void	pipeline_execution(char **env)
{
	int		ends[2];
	pid_t	id;
	t_parse	*cmd_list;
	int		fd_in;

	fd_in = STDIN_FILENO;
	checker();
	cmd_list = g_mini.command;
	while (cmd_list->next)
	{
		pipe(ends);
		id = fork();
		if (id == 0)
		{
			dup_ends(ends, fd_in);
			redirection_helper(cmd_list);
			execute_cmd(cmd_list, env);
		}
		close_ends(ends, fd_in);
		fd_in = ends[READ_END];
		cmd_list = cmd_list->next;
	}
	exec_last_cmd(cmd_list, fd_in, ends, env);
	parent_process();
}
