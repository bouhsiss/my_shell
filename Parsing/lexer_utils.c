/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:49:07 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/27 19:52:43 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isop(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' 
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && (int)lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}
void lexer_retreat(t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		lexer->i--;
		lexer->c = lexer->contents[lexer->i];
	}
}

t_lexer	*init_lexer(char *contents)
{
	t_lexer *lexer;
	

	lexer = malloc(sizeof(struct s_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return lexer;
}

t_token *err_quotes(char *val)
{
	free(val);
	g_mini.l_err = 1;
	return (NULL);
}

t_token *free_retnull(char *val)
{
	free(val);
	return (NULL);
}