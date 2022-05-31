/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:47 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/31 13:35:17 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	exec_last_cmd(t_parse *cmd_list, int fd_in, int *ends, t_envlist **env)
{
	pid_t	id;

	if (fd_in == 0 && !cmd_list->redirection && cmd_list->cmd)
	{
		if (builtincheck(cmd_list->cmd))
			return (executebuiltin(cmd_list, env));
	}
	g_mini.flag = 1;
	id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (fd_in != STDIN_FILENO)
			dupfd2fd(fd_in, STDIN_FILENO);
		if (ends[WRITE_END] > 2)
			close(ends[WRITE_END]);
		redirection_helper(cmd_list);
		if (cmd_list->cmd && builtincheck(cmd_list->cmd))
			exit(executebuiltin(cmd_list, env));
		else
			execute_cmd(cmd_list, env);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	return (0);
}

void	checker(t_parse *cmd_list)
{
	if (cmd_list->cmd)
	{
		if (ft_strcmp(cmd_list->cmd, "CD"))
			return ;
		else if (ft_strcmp(cmd_list->cmd, "EXPORT"))
			return ;
		else if (ft_strcmp(cmd_list->cmd, "UNSET"))
			return ;
		else if (ft_strcmp(cmd_list->cmd, "EXIT"))
			return ;
		else
			cmd_list->cmd = lowcase(cmd_list->cmd);
	}
}

void	parent_process(void)
{
	int	stat_loc;

	while (waitpid(-1, &stat_loc, 0) > 0)
	{
		if (WIFEXITED(stat_loc))
			g_mini.exit_code = WEXITSTATUS(stat_loc);
		else if (WIFSIGNALED(stat_loc))
		{
			if (WTERMSIG(stat_loc) == SIGQUIT)
				dprintf(2, "Quit: 3\n");
			g_mini.exit_code = WTERMSIG(stat_loc) + 128;
		}
	}
	g_mini.flag = 0;
}

void	pipeline_execution(t_envlist **envlist)
{
	int		ends[2];
	t_parse	*cmd_list;
	int		fd_in;

	fd_in = STDIN_FILENO;
	cmd_list = g_mini.command;
	while (cmd_list->next)
	{
		checker(cmd_list);
		pipe(ends);
		launch_child(fd_in, ends, cmd_list, envlist);
		close_ends(ends, fd_in);
		fd_in = ends[READ_END];
		cmd_list = cmd_list->next;
	}
	exec_last_cmd(cmd_list, fd_in, ends, envlist);
	parent_process();
}
