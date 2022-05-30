/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:49:07 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/30 15:52:51 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isop(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(struct s_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

t_token	*err_quotes(char *val)
{
	free(val);
	g_mini.l_err = 1;
	return (NULL);
}
