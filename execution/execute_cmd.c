#include"minishell.h"

int	findp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_paths(char **envp, int p, char *cmd)
{
	char	**path;
	char	**path_temp;
	int		i;

	i = 0;
	path_temp = ft_split(envp[p], '=');
	path = ft_split(path_temp[1], ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}
void execute_cmd(t_parse *cmd_list, char **env)
{
	char *path;


	if(cmd_list->cmd)
	{
		path = ft_paths(env, findp(env), cmd_list->cmd);
		if (execve(path, cmd_list->args, env) == -1)
			exit(127);
		exit(0);
	}
}