/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:52:56 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/27 19:52:40 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_collect_word(t_lexer *lexer)
{
	char *val;
	char *s;
	
	val = ft_strdup("");
	while(!isop(lexer->c) && !ft_isspace(lexer->c) && lexer->c != '\0')
	{
		
		if (lexer->c == '\'' || lexer->c == '\"')
		{
			s = join_string(lexer, lexer->c);
			val = ft_strjoin(val, s);
			break ;
		}
		else if (lexer->c == '$')
		{
			s = expandInWord(lexer);
			lexer_retreat(lexer);
		}
		else
			s = lexer_get_current_char_as_string(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	if (val[0] == '\0')
		return (free_retnull(val));
	return (init_token(T_WORD, val));
}

char	*join_word(t_lexer *lexer)
{
	char	*val;
	char	*s;

	val = ft_strdup("");
	while (!isop(lexer->c) && !ft_isspace(lexer->c) && lexer->c != '\0')
	{
		if (lexer->c == '\'' || lexer->c == '\"')
		{
			s = join_string(lexer, lexer->c);
			val = ft_strjoin(val, s);
			break ;
		}
		else if (lexer->c == '$')
		{
			s = expandInQuotes(lexer);
			lexer_retreat(lexer);
		}
		else
			s = lexer_get_current_char_as_string(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	if (val[0] == '\0')
		return ((char *)free_retnull(val));
	return (val);
}

char	*after_quotes(t_lexer *lexer, char *val)
{
	if (lexer->c == '\'' || lexer->c == '\"')
		return (ft_strjoin(val, join_string(lexer, lexer->c)));
	else
		return (ft_strjoin(val, join_word(lexer)));
}


t_token *lexer_collect_string(t_lexer *lexer, char c)
{
	char	*val;
	char	*s;

	val = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && c == '\"')
		{
			s = expandInQuotes(lexer);
			lexer_retreat(lexer);
		}
		else
			s = lexer_get_current_char_as_string(lexer);			
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	if (lexer->c != c)
		return (err_quotes(val));
	lexer_advance(lexer);
	if (!isop(lexer->c) && !ft_isspace(lexer->c) && lexer->c != '\0')
		val = after_quotes(lexer, val);
	return (init_token(T_WORD, val));
}

char *join_string(t_lexer *lexer, char c)
{
	char	*val;
	char	*s;

	val = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && c == '\"')
		{
			s = expandInQuotes(lexer);
			lexer_retreat(lexer);
		}		
		else
			s = lexer_get_current_char_as_string(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	if (lexer->c != c)
		g_mini.l_err = 1;
	lexer_advance(lexer);
	if (!isop(lexer->c) && !ft_isspace(lexer->c) && lexer->c != '\0')
		val = after_quotes(lexer, val);
	return (val);
}
