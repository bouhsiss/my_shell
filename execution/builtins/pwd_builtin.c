#include"minishell.h"

int pwd_builtin()
{
	char *pwd;
	char *buff = NULL;

	pwd = getcwd(buff, 1024);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return(EXIT_SUCCESS);
}
