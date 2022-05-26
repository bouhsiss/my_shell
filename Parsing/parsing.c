/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:42:01 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/26 11:09:58 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_command(t_token **token)
{
	t_parse *command;
	int i;

	mini.command = init_commands();
	i = 0;
	command = mini.command;
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
	t_type before;
	t_type curr;
	int i;

	i = 0;
	before = -1;
	while (token[i])
	{
		curr = token[i]->type;
		if (before != T_WORD && i!= 0 && curr != T_WORD
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

void throw_syntax(int err)
{
	if (err == 1)
		ft_putstr_fd("BASH: syntax error!\n", 2);
	if (err == 2)
		ft_putstr_fd("BASH: Open Quotes!\n", 2);
}

void	free_all(void)
{
	if (mini.line)
		free(mini.line);
	free_command();
	mini.line = NULL;
	mini.command = NULL;
}

void parse(void)
{
	t_lexer *lexer;
	t_token **token;
	int i;
	
	lexer = init_lexer(mini.line);
	token = malloc(sizeof(struct s_token *) * 2);
	i = 0;
	token[0] = lexer_get_next_token(lexer);
	token[1] = NULL;
	while (token[i] != NULL)
	{
		i++;
		token = realloc_token(token, lexer_get_next_token(lexer));
	}
	if (!syntax(token))
		throw_syntax(1);
	else if (mini.l_err == 1)
		throw_syntax(2);
	else
		create_command(token);
	free_token(token);
	free(lexer);
}