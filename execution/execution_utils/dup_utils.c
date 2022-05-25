/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:08:36 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/25 13:32:25 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	dupfd2fd(int fd, int othe_fd)
{
	dup2(fd, othe_fd);
	close(fd);
}

void	dup_ends(int *ends, int fd_in)
{
	if (fd_in != STDIN_FILENO)
		dupfd2fd(fd_in, STDIN_FILENO);
	dupfd2fd(ends[WRITE_END], STDOUT_FILENO);
	close(ends[READ_END]);
}

void	close_ends(int *ends, int fd_in)
{
	if (ends[WRITE_END] > 2)
		close(ends[WRITE_END]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}
