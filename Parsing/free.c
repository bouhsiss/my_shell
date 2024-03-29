/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:04:41 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/06 18:31:11 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_redirection *rdr)
{
	t_redirection	*current;
	t_redirection	*temp;

	current = rdr;
	while (current)
	{
		free(current->file);
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	free_command(void)
{
	t_parse		*current;
	t_parse		*tmp;
	int			i;

	if (g_mini.command == NULL)
		return ;
	current = g_mini.command;
	while (current)
	{
		if (current->cmd)
			free(current->cmd);
		i = 0;
		while (current->args && current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		if (current->args)
			free(current->args);
		free_redirections(current->redirection);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	free_all(void)
{
	g_mini.l_err = 0;
	if (g_mini.line)
		free(g_mini.line);
	free_command();
	g_mini.line = NULL;
	g_mini.command = NULL;
}

t_token	*free_retnull(char *val)
{
	free(val);
	return (NULL);
}
