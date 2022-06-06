/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:02:39 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/06/06 17:17:20 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_key_unset(char *key)
{
	int	i;

	i = 0;
	if (char_isdigit(key) == 0 || (key[0] >= '0' && key[0] <= '9'))
	{
		error_message(key, "not a valid identifier");
		return (0);
	}
	return (1);
}

void	delete_envvar(t_envlist **envlist, char *key)
{
	t_envlist	*temp;
	t_envlist	*prev;

	temp = (*envlist);
	if (temp && (ft_strcmp(temp->key, key) == 0))
	{
		*envlist = temp->next;
		free(temp);
		return ;
	}
	while (temp && ft_strcmp(temp->key, key))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}

int	unset_builtin(t_parse *cmd_list)
{
	t_envlist	*env;
	int			i;

	i = 1;
	env = g_mini.envlist;
	while (cmd_list->args[i])
	{
		if (check_key_unset(cmd_list->args[i]))
			delete_envvar(&env, cmd_list->args[i]);
		else
		{
			g_mini.exit_code = 1;
			return (g_mini.exit_code);
		}
		i++;
	}
	g_mini.exit_code = 0;
	return (g_mini.exit_code);
}
