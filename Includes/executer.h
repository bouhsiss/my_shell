/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:17:43 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/25 10:51:03 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdbool.h>


# define WRITE_END 1
# define READ_END 0
# define IN_REDR 1
# define OUT_REDR 2
# define HEREDOC_REDR 3
# define APPEND_REDR 4


void pipeline_execution(char **env);
int	ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
void dupper(int fd_in, int *ends,t_parse *cmd_list, int fd_out);
int	ft_strcmp(char *s1, char *s2);
int openf_in(char *file);
void	ft_putendl_fd(char *s, int fd);
void name_generator();
void implement_heredoc();
void unlink_heredocs();
void redirection_helper(t_parse *cmd_list);
void dupfd2fd(int fd, int othe_fd);
void dup_ends(int *ends, int fd_in);
char *lowcase(char *str);
void execute_cmd(t_parse *cmd_list, char **env);

#endif
