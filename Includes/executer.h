/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:17:43 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/20 20:12:33 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

void execute(char **env);
int	ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
char *name_generator();
void dupper(int fd_in, int *ends,t_parse *cmd_list, int fd_out);
int	ft_strcmp(char *s1, char *s2);
int openf_in(char *file);
void	ft_putendl_fd(char *s, int fd);
int open_heredoc(char *filename, char *delimiter, int flag);
char *name_generator();

#endif
