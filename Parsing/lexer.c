/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:01:09 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/30 15:50:48 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_operator(t_lexer *lexer)
{
	if (lexer->c == '|')
		return (lex_av_tok(lexer, init_tok(T_PIPE, lex_crr_str(lexer))));
	else if (lexer->c == '<')
	{
		if (lexer->contents[lexer->i + 1] == '<')
		{
			lexer_advance(lexer);
			return (lex_av_tok(lexer, init_tok(T_HEREDOC, lex_crr_str(lexer))));
		}
		return (lex_av_tok(lexer, init_tok(T_RDRIN, lex_crr_str(lexer))));
	}
	else if (lexer->c == '>')
	{
		if (lexer->contents[lexer->i + 1] == '>')
		{
			lexer_advance(lexer);
			return (lex_av_tok(lexer, init_tok(T_APPEND, lex_crr_str(lexer))));
		}
		return (lex_av_tok(lexer, init_tok(T_RDROUT, lex_crr_str(lexer))));
	}
	return (NULL);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
		lexer_advance(lexer);
}

t_token	*lex_next_tok(t_lexer *lexer)
{
	while (lexer->c != '\0' && (int)lexer->i < ft_strlen(lexer->contents))
	{
		if (ft_isspace(lexer->c))
			lexer_skip_whitespace(lexer);
		if (!isop(lexer->c) && lexer->c != '\'' && lexer->c != '\"')
			return (lexer_collect_word(lexer));
		if (lexer->c == '\"')
			return (lexer_collect_string(lexer, lexer->c));
		if (lexer->c == '\'')
			return (lexer_collect_string(lexer, lexer->c));
		return (get_operator(lexer));
	}
	return (NULL);
}

t_token	*lex_av_tok(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lex_crr_str(t_lexer *lexer)
{
	char	*s;

	s = malloc(sizeof(char) * 2);
	s[0] = lexer->c;
	s[1] = '\0';
	return (s);
}
