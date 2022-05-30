/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:20:37 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/30 22:15:45 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expandinquotes(t_lexer *lexer)
{
	char	*val;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == '\"' || lexer->c == ' ' || lexer->c == '$')
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit(lexer));
	val = ft_strdup("");
	while (lexer->c != '\"' && lexer->c != ' '
		&& lexer->c != '\0' && lexer->c != '$' && lexer->c != '\'')
	{
		s = lex_crr_str(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	s = my_getenv(val);
	free(val);
	if (lexer->c == '$')
		s = ft_strjoin(s, expandinquotes(lexer));
	return (s);
}

char	*expandcheck(t_lexer *lexer, char *s)
{
	if (lexer->c == '$')
		s = ft_strjoin(s, expandinword(lexer));
	if ((lexer->c == ' ' ) || (s && s[0] == '\0'))
		s = ft_strjoin(s, ft_strdup(" "));
	if (lexer->c == '\'' || lexer->c == '\"')
		s = ft_strjoin(s, join_string(lexer, lexer->c));
	return (s);
}

char	*expandinword(t_lexer *lexer)
{
	char	*val;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == '\"' || lexer->c == '$'
		|| lexer->c == ' ' || lexer->c == '\0' )
		return (ft_strdup("$"));
	if (lexer->c == '?')
		return (expand_exit(lexer));
	val = ft_strdup("");
	while (!isop(lexer->c) && !ft_isspace(lexer->c)
		&& lexer->c != '\0' && lexer->c != '$' && lexer->c
		!= '\'' && lexer->c != '\"')
	{
		s = lex_crr_str(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	s = my_getenv(val);
	free(val);
	s = expandcheck(lexer, s);
	return (s);
}

char	*expand_exit(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (ft_itoa(g_mini.exit_code));
}
