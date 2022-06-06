#include"minishell.h"

char	charsrch(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
		{
			return (0);
		}
		str++;
	}
	return (c);
}