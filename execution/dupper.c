#include"minishell.h"


char *name_generator()
{
	char *filename=NULL;
	int fd;
	int rand;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &rand, sizeof(rand));
	if (rand < 0)
		rand *= -1;
	rand = rand/1000000;
	filename=ft_strjoin("/tmp/tmp", ft_itoa(rand));
	return(filename);
}


int open_heredoc(char *filename, char *delimiter, int flag)
{
	int temp;
	char *rl;


	temp = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while(1)
	{
		rl = readline(">");
		if (ft_strcmp(rl, delimiter) == 0)
			break ;
		ft_putendl_fd(rl, temp);
	}
	close(temp);
	if(flag == 0)
		unlink(filename);
	return(open(filename, O_RDONLY));
}

void fd_in_dup(int fd_in, t_parse *cmd_list)
{
	t_redirection *redr;
	char *filename;

	redr = cmd_list->redirection;
	while(redr)
	{
		if (redr->type == 1)
			fd_in = openf_in(redr->file);
		else if(redr->type == 3)
		{
			filename = name_generator();
			fd_in=open_heredoc(filename, redr->file, 1);
		}
		redr = redr->next;
	}
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (filename != NULL)
		unlink(filename);
}

void fd_out_dup(int fd_out, t_parse *cmd_list, int *ends)
{
	t_redirection *redr;

	redr = cmd_list->redirection;
	if (cmd_list->next != NULL)
		fd_out = ends[1];
	while(redr)
	{
		if (redr->type == 2)
			fd_out = open(redr->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (redr->type == 4)
			fd_out = open(redr->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		redr = redr->next;
	}
	if (fd_out != 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
}

void dupper(int fd_in, int *ends,t_parse *cmd_list, int fd_out)
{
	fd_in_dup(fd_in, cmd_list);
	fd_out_dup(fd_out, cmd_list, ends);
}