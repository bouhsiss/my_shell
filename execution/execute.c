/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:13:15 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/09 22:46:59 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *lowcase(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;	
	}
	return(str);
}

int count_and_lowcase()
{
	int count;
	t_parse *cmd_list;

	count = 0;
	cmd_list = mini.command;
	while(cmd_list)
	{
		if (cmd_list->cmd)
			count++;
		cmd_list->cmd = lowcase(cmd_list->cmd);
		cmd_list = cmd_list->next;
	}
	return(count);
}

char **bin_path(char **env)
{
	int i;
	char **path=NULL;
	
	i = 0;

	while(env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i], '=');
			path = ft_split(path[1], ':');
			return(path);
		}
		i++;
	}
	return(path);
}

void execute(char **env)
{
	int cmds_nbr;
	int id;
	char **path;
	int i=0;
	
	path = bin_path(env);
	cmds_nbr = count_and_lowcase();
	while(cmds_nbr > 1)
	{
		 
	}
}