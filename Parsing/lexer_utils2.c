/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:50:36 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/30 15:53:04 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*our_getenv(char *key)
{
	t_envlist	*current;

	if (!key)
		return (NULL);
	current = g_mini.envlist;
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	if (ft_strcmp(current->key, key) == 0)
		return (current);
	return (NULL);
}

char	*my_getenv(char *key)
{
	t_envlist	*new;

	new = our_getenv(key);
	if (new != NULL)
		return (ft_strdup(new->value));
	else
		return (ft_strdup(""));
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && (int)lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_retreat(t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		lexer->i--;
		lexer->c = lexer->contents[lexer->i];
	}
}
