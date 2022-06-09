/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:42:01 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/06 18:27:09 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_command(t_token **token)
{
	t_parse	*command;
	int		i;

	g_mini.command = init_commands();
	i = 0;
	command = g_mini.command;
	while (token[i])
	{
		factory(token, command, i);
		if (token[i]->type == T_RDRIN || token[i]->type == T_RDROUT
			|| token[i]->type == T_APPEND || token[i]->type == T_HEREDOC)
			i++;
		if (token[i]->type == T_PIPE)
		{
			command->next = add_command();
			command = command->next;
		}
		i++;
	}
}

int	syntax(t_token **token)
{
	t_type	before;
	t_type	curr;
	int		i;

	i = 0;
	before = -1;
	while (token[i])
	{
		curr = token[i]->type;
		if (before != T_WORD && i != 0 && curr != T_WORD
			&& before != T_PIPE && curr != T_PIPE)
			return (0);
		if (i == 0 && curr == T_PIPE)
			return (0);
		before = curr;
		i++;
	}
	if (curr != T_WORD)
		return (0);
	return (1);
}

int	throw_syntax(int err)
{
	if (err == 1)
		ft_putstr_fd("BASH: syntax error!\n", 2);
	if (err == 2)
		ft_putstr_fd("BASH: Open Quotes!\n", 2);
	g_mini.exit_code = 258;
	return (0);
}

void	parse(void)
{
	t_lexer	*lexer;
	t_token	**token;
	int		i;

	lexer = init_lexer(g_mini.line);
	token = malloc(sizeof(struct s_token *) * 2);
	i = 0;
	token[0] = lex_next_tok(lexer);
	token[1] = NULL;
	while (token[i] != NULL)
	{
		i++;
		token = realloc_token(token, lex_next_tok(lexer));
	}
	if (!syntax(token))
		throw_syntax(1);
	else if (g_mini.l_err == 1)
		throw_syntax(2);
	else
		create_command(token);
	free_token(token);
	free(lexer);
}
