#include"minishell.h"

void	exit_with_arg(t_parse *cmd_list)
{
	if (char_isdigit(cmd_list->args[1]))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		error_message("exit", "numeric argument required");
		g_mini.exit_code = 255;
		exit (g_mini.exit_code);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		g_mini.exit_code = ft_atoi(cmd_list->args[1]);
		exit(g_mini.exit_code);
	}
}

int	exit_builtin(t_parse *cmd_list)
{
	if (cmd_list->args[2])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		error_message("exit", "too many arguments");
		g_mini.exit_code = 1;
		return (g_mini.exit_code);
	}
	if (!cmd_list->args[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(g_mini.exit_code);
	}
	else
		exit_with_arg(cmd_list);
	return (0);
}
