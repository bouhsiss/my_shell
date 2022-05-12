/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:17:43 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/12 17:47:52 by hbouhsis         ###   ########.fr       */
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


#endif
