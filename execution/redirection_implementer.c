/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_implementer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:55 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/30 22:32:24 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	dup_redr(t_parse *cmd_list, int fd_in, int fd_out)
{
	int				in_flag;
	int				out_flag;
	t_redirection	*red;

	in_flag = 0;
	out_flag = 0;
	red = cmd_list->redirection;
	while (red != NULL)
	{
		if (red->type == IN_REDR || red->type == HEREDOC_REDR)
			in_flag = 1;
		if (red->type == OUT_REDR || red->type == APPEND_REDR)
			out_flag = 1;
		red = red->next;
	}
	if (in_flag)
		dupfd2fd(fd_in, STDIN_FILENO);
	if (out_flag)
		dupfd2fd(fd_out, STDOUT_FILENO);
}

int	check_for_in_redr(t_redirection *redr, int fd_in)
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (redr->type == IN_REDR)
		return (open(redr->file, O_RDONLY, 0644));
	else if (redr->type == HEREDOC_REDR)
		return (open(redr->file, O_RDONLY, 0644));
	return (fd_in);
}

int	check_for_out_redr(t_redirection *redr, int fd_out)
{
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (redr->type == OUT_REDR)
		return (open(redr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redr->type == APPEND_REDR)
		return (open(redr->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (fd_out);
}

void	redirection_helper(t_parse *cmd_list)
{
	int				fd_in;
	int				fd_out;
	t_redirection	*redr;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (cmd_list->redirection)
	{
		redr = cmd_list->redirection;
		while (redr)
		{
			if (redr->type == IN_REDR || redr->type == HEREDOC_REDR)
				fd_in = check_for_in_redr(redr, fd_in);
			else if (redr->type == OUT_REDR || redr->type == APPEND_REDR)
				fd_out = check_for_out_redr(redr, fd_out);
			if (fd_in < 0 || fd_out < 0)
			{
				error_message(redr->file, "");
				g_mini.exit_code = EXIT_FAILURE;
				exit(g_mini.exit_code);
			}
			redr = redr->next;
		}
		dup_redr(cmd_list, fd_in, fd_out);
	}
}
