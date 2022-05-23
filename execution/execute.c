#include"minishell.h"

void dupfd2fd(int fd, int othe_fd)
{
	dup2(fd, othe_fd);
	close(fd);
}

void dup_redr(t_parse *cmd_list, int fd_in, int fd_out)
{
	int in_flag = 0;
	int out_flag = 0;
	t_redirection *red = cmd_list->redirection;
	while (red != NULL) {
		if (red->type == IN_REDR || red->type == HEREDOC_REDR)
			in_flag = 1;
		if (red->type == OUT_REDR || red->type == APPEND_REDR)
			out_flag = 1;
		red = red->next;
	}
	if (in_flag)
		dupfd2fd(fd_in, STDIN_FILENO);
	if (out_flag)
		dupfd2fd(fd_out, STDOUT_FILENO);
}

void redirection_helper(t_parse *cmd_list)
{
	int fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;

	t_redirection *redr = cmd_list->redirection;
	while(redr)
	{
		if (redr->type == IN_REDR || redr->type == HEREDOC_REDR)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			if (redr->type == IN_REDR)
				fd_in = open(redr->file, O_RDONLY, 0644);
			if (redr->type == HEREDOC_REDR)
				fd_in = open(redr->file, O_RDONLY, 0644);
		}
		else if(redr->type == OUT_REDR || redr->type == APPEND_REDR)
		{
			if (fd_out != STDOUT_FILENO)
				close(fd_out);
			if(redr->type == OUT_REDR)
				fd_out = open(redr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (redr->type == APPEND_REDR)
				fd_out = open(redr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}	
		redr = redr->next;
	}
	dup_redr(cmd_list, fd_in, fd_out);
}

void exec_last_cmd(t_parse *cmd_list, int fd_in, int *ends)
{
	pid_t  id;

	id = fork();
	if (id == 0)
	{
		if (fd_in != STDIN_FILENO)
			dupfd2fd(fd_in, STDIN_FILENO);
		if (ends[WRITE_END] > 2)
			close(ends[WRITE_END]);
		if (cmd_list->redirection)
			redirection_helper(cmd_list);
		if (cmd_list->cmd)
		{
			if (execvp(cmd_list->args[0], cmd_list->args) == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
		exit(EXIT_FAILURE);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}

void execute(char **env)
{
	(void)env;
	int ends[2];
	pid_t id;
	t_parse *cmd_list;
	int fd_in = STDIN_FILENO;

	cmd_list=mini.command;
	while(cmd_list->next)
	{
		pipe(ends);
		id = fork();
		if (id == 0)
		{
			if(fd_in != STDIN_FILENO)
				dupfd2fd(fd_in, STDIN_FILENO);
			if(ends[WRITE_END] != STDOUT_FILENO)
				dupfd2fd(ends[WRITE_END], STDOUT_FILENO);
			if (ends[READ_END] > 2)
				close(ends[READ_END]);
			if (cmd_list->redirection)
				redirection_helper(cmd_list);
			if (cmd_list->cmd != NULL)
			{
				if (execvp(cmd_list->args[0], cmd_list->args) == -1)
				{
					exit(69420);
				}
			}
			exit(666);
		}
		if(ends[WRITE_END] > 2)
			close(ends[WRITE_END]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		fd_in = ends[READ_END];
		cmd_list = cmd_list->next;
	}
	exec_last_cmd(cmd_list, fd_in, ends);
	while(wait(0) > 0);
}