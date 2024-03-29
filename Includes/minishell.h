/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:37:11 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/06 18:32:31 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "parser.h"
# include "executer.h"

typedef struct s_minishell
{
	t_parse		*command;
	char		*line;
	int			l_err;
	t_envlist	*envlist;
	int			exit_code;
	pid_t		id;
}	t_mini;

t_mini	g_mini;

char	*ft_strdup(char *s);
int		isop(char c);
int		ft_isspace(int c);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
void	free_token(t_token **token);
void	catch_signal(void);
#endif