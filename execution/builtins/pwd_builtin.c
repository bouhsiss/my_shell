/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:06:15 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/30 22:28:55 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	pwd_builtin(void)
{
	char	*pwd;
	char	*buff;

	buff = NULL;
	pwd = getcwd(buff, 1024);
	if (pwd == NULL)
	{
		error_message("pwd", "");
		g_mini.exit_code = 1;
		return (g_mini.exit_code);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_mini.exit_code = 0;
	return (g_mini.exit_code);
}
