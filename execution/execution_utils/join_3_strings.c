#include"minishell.h"

static char	*ft_strcat(char	*dest, char	*src)
{
	int	i;
	int	destlen;

	i = 0;
	destlen = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

static char	*ft_strcpy(char	*dest, char	*src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char *join_3_strings(char *s1, char *s2, char *s3)
{
	int total;
	char *str;

	total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc((total+1) * sizeof(char));
	if (!str)
		return(NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	ft_strcat(str, s3);
	return(str);
}