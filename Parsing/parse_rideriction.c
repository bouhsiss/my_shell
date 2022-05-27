/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rideriction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 03:57:57 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/26 11:04:32 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection *init_redirection(char *val, t_type type)
{
	t_redirection *redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	redirection->file = ft_strdup(val);
	redirection->type = type;
	redirection->next = NULL;
	return (redirection);
}

void	add_redirecion(t_redirection *head, char *val, t_type type)
{
	t_redirection *current;
	t_redirection *new;

	current = head;
	while (current->next != NULL)
		current = current->next;
	new = (t_redirection *)malloc(sizeof(t_redirection));
	new->file = ft_strdup(val);
	new->type = type;
	new->next = NULL;
	current->next = new;
}

void free_redirections(t_redirection *rdr)
{
	t_redirection *current;
	t_redirection *temp;
	
	current = rdr;
	while (current)
	{
		free(current->file);
		temp = current;
		current = current->next;
		free(temp);
	}
}