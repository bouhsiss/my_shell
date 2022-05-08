/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:53:58 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/08 14:34:51 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_lexer *lexer;
	t_token *token;
	char *buffer;
	
	token = NULL;
	while(1)
	{
		
		buffer = readline("MINISHELL 🥵:");
		if (buffer == NULL)
			break ;
		lexer = init_lexer(buffer);
		add_history(buffer);
		while((token = lexer_get_next_token(lexer)) != NULL)
		{
			printf("TOKEN(%d, %s)\n", token->type, token->value);
		}
	}
	return 0;
}
