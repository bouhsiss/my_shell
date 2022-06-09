/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:02:08 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/31 11:02:09 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
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
	return (str);
}
