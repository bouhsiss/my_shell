/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:17:43 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/28 18:50:27 by hbouhsis         ###   ########.fr       */
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

typedef struct s_envlist
{
	char				*key;
	char				*value;
	char				sep;
	struct s_envlist	*next;
}		t_envlist;

char	*ft_strjoin2(char *s1, char *s2);
void		pipeline_execution(t_envlist **envlist);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		**ft_split(char const *s, char c);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);
void		dupper(int fd_in, int *ends, t_parse *cmd_list, int fd_out);
int			ft_strcmp(char *s1, char *s2);
void		ft_putendl_fd(char *s, int fd);
void		implement_heredoc(void);
void		unlink_heredocs(void);
void		redirection_helper(t_parse *cmd_list);
void		dupfd2fd(int fd, int othe_fd);
void		dup_ends(int *ends, int fd_in);
char		*lowcase(char *str);
void		execute_cmd(t_parse *cmd_list,t_envlist **envlist);
void		close_ends(int *ends, int fd_in);
char		*env_value(t_envlist **env, char *key);
t_envlist	*env_builder(char **env);
void		free_array(char **arr);
void		ft_putchar_fd(char c, int fd);
int			char_isdigit(char *str);
void 		error_message(char *cmd, char *message);
void		envlist_addback(t_envlist **env, t_envlist *new);
t_envlist	*envlist_new(char *key, char *value);
char **envlist_to_envarr(t_envlist **envlist);
char *join_3_strings(char *s1, char *s2, char *s3);
int unset_builtin(t_parse *cmd_list);
//===== builtins  =====
int			echo_builtin(char **args);
int			cd_builtin(char **args, t_envlist *env);
int			pwd_builtin(void);
int			env_builtin(void);
int 		export_builtin(t_parse *cmd_list);


#endif
