#include"minishell.h"

void dupfd2fd(int fd, int othe_fd)
{
	dup2(fd, othe_fd);
	close(fd);
}

void dup_ends(int *ends, int fd_in)
{
	if (fd_in != STDIN_FILENO)
		dupfd2fd(fd_in, STDIN_FILENO);
	dupfd2fd(ends[WRITE_END], STDOUT_FILENO);
	close(ends[READ_END]);
}