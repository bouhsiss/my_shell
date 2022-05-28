/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:01:09 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/28 16:43:46 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_operator(t_lexer *lexer)
{
	if (lexer->c == '|')
		return (lexer_advance_with_token(lexer, init_token(T_PIPE, lexer_get_current_char_as_string(lexer))));
	else if (lexer->c == '<')
	{
		if (lexer->contents[lexer->i + 1] == '<') 
		{
			lexer_advance(lexer);
			return (lexer_advance_with_token(lexer, init_token(T_HEREDOC, lexer_get_current_char_as_string(lexer))));
		}
		return (lexer_advance_with_token(lexer, init_token(T_RDRIN, lexer_get_current_char_as_string(lexer))));
	}
	else if (lexer->c == '>')
	{
		if (lexer->contents[lexer->i + 1] == '>')
		{
			lexer_advance(lexer);
			return (lexer_advance_with_token(lexer, init_token(T_APPEND, lexer_get_current_char_as_string(lexer))));
		}
		return (lexer_advance_with_token(lexer, init_token(T_RDROUT, lexer_get_current_char_as_string(lexer))));
	}
	return (NULL);
}

void lexer_skip_whitespace(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
		lexer_advance(lexer);
}

t_token *lexer_get_next_token(t_lexer *lexer)
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
		return get_operator(lexer);
	}
	return (NULL);
}


t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);

	return (token);
}

char *lexer_get_current_char_as_string(t_lexer *lexer)
{
	char *s;

	s = malloc(sizeof(char) * 2);
	s[0] = lexer->c;
	s[1] = '\0';

	return s;
}

t_envlist *our_getenv(char *key)
{
    t_envlist *current;
    if (!key)
        return NULL;
    current = g_mini.envlist;
    while (current->next != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    if (ft_strcmp(current->key, key) == 0)
        return current;
    return NULL;
}

char *my_getenv(char *key)
{
    t_envlist *new;

    new = our_getenv(key);
    if (new != NULL)
        return (ft_strdup(new->value));
    else
        return (ft_strdup(""));
    // return (getenv(key));
}

char *expandInQuotes(t_lexer *lexer)
{
	char	*val;
	char	*s;
	
	lexer_advance(lexer);
	if (lexer->c == '\"' || lexer->c == ' ' || lexer->c == '$')
		return (ft_strdup("$"));
	val = ft_strdup("");
	while (lexer->c != '\"' && lexer->c != ' ' && lexer->c != '\0' && lexer->c !='$' && lexer->c != '\'')
	{
		s = lexer_get_current_char_as_string(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	s = my_getenv(val);
	free(val);
	if (lexer->c == '$')
		s = ft_strjoin(s, expandInQuotes(lexer));
	return (s);
}

char	*expandCheck(t_lexer *lexer, char *s)
{
	if (lexer->c == '$')
		s = ft_strjoin(s, expandInWord(lexer));
	if ((lexer->c == ' ' ) || (s && s[0] == '\0'))
		s = ft_strjoin(s, ft_strdup(" "));
	if (lexer->c == '\'' || lexer->c == '\"')
		s = ft_strjoin(s, join_string(lexer, lexer->c));
	return (s);
}

char *expandInWord(t_lexer *lexer)
{
	char	*val;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == '\"' || lexer->c == '$'
		|| lexer->c == ' ' || lexer->c == '\0' )
		return (ft_strdup("$"));
	val = ft_strdup("");
	while (!isop(lexer->c) && !ft_isspace(lexer->c) && lexer->c != '\0' && lexer->c != '$' && lexer->c
		!= '\'' && lexer->c != '\"')
	{
		s = lexer_get_current_char_as_string(lexer);
		val = ft_strjoin(val, s);
		lexer_advance(lexer);
	}
	s = my_getenv(val);
	free(val);
	s = expandCheck(lexer, s);
	return (s);
}	