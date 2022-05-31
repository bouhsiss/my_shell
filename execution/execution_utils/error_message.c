/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:04:23 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/31 11:04:25 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	error_message(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
