#include"minishell.h"

void exec_last_cmd(t_parse *cmd_list, int fd_in, int *ends, char **env)
{
	pid_t  id;
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

void checker()
{
	t_parse *cmd_list;

	cmd_list = mini.command;
	while(cmd_list)
	{
		cmd_list->cmd = lowcase(cmd_list->cmd);
		cmd_list = cmd_list->next;
	}
}


void pipeline_execution(char **env)
{
	int ends[2];
	pid_t id;
	t_parse *cmd_list;
	int fd_in = STDIN_FILENO;

	checker();
	cmd_list=mini.command;
	while(cmd_list->next)
	{
		pipe(ends);
		id = fork();
		if (id == 0)
		{
			dup_ends(ends, fd_in);
			redirection_helper(cmd_list);
			execute_cmd(cmd_list, env);
		}
		if (ends[WRITE_END] > 2)
			close(ends[WRITE_END]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		fd_in = ends[READ_END];
		cmd_list = cmd_list->next;
	}
	exec_last_cmd(cmd_list, fd_in, ends, env);
	int exit_code;
	int stat_loc;
	while (waitpid(-1, &stat_loc, 0) > 0) {
		if (WIFEXITED(stat_loc))
			exit_code = WEXITSTATUS(stat_loc);
	}
	printf("\n-------------\nparent returned -> exit_code = %d\n-------------\n", exit_code);
	while(wait(0) > 0);
}