#include"minishell.h"

char *env_value(char **env, char *value)
{
	int i;
	char **temp;

	i  = 0;
	while(env[i])
	{
		if (ft_strncmp(env[i], value, ft_strlen(value))==0)
		{
			temp = ft_split(env[i], '=');
			return(temp[1]);
		}
		i++;
	}
	return(NULL);
}

void cd_home(char **env)
{
	char *home_path;

	home_path = env_value(env, "HOME=");
	chdir(home_path);
}

int cd_builtin(char **args,char **env)
{
	if (!args[1])
		cd_home(env);
	else
		chdir(args[1]);
	return(EXIT_SUCCESS);
}