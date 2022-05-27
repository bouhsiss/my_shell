/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:36:49 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/26 10:40:39 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*str;
	int			i;
	int			j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
char *ft_strdup(char *s)
{
	char *p;
	int i;

	i = 0;
	while (s[i])
		i++;
	p = (char *)malloc(i + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	char	sym;

	ptr = (char *)str;
	sym = (char)c;
	while (*ptr && !(*ptr == sym))
		ptr++;
	if (*ptr == sym)
		return (ptr);
	else
		return (NULL);
}
