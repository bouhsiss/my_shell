#include"minishell.h"

int	builtincheck(char *cmd)
{
	char	*builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int		i;

	i = 0;
	while (i < 7)
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	executebuiltin(t_parse *cmd_list, t_envlist **envlist)
{
	if (!ft_strcmp("echo", cmd_list->cmd))
		return (echo_builtin(cmd_list->args));
	if (!ft_strcmp("cd", cmd_list->cmd))
		return (cd_builtin(cmd_list->args, (*envlist)));
	if (!ft_strcmp("pwd", cmd_list->cmd))
		return (pwd_builtin());
	if (!ft_strcmp("export", cmd_list->cmd))
		return (export_builtin(cmd_list));
	if (!ft_strcmp("unset", cmd_list->cmd))
		return (unset_builtin(cmd_list));
	if (!ft_strcmp("env", cmd_list->cmd))
		return (env_builtin());
	return (88);
}
