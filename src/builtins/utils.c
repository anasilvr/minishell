#include "minishell.h"

void	free_tab(char **old_tab)
{
	int i;

	if (!old_tab)
		return ;
	i = -1;
	while (old_tab[++i] != NULL)
		xfree(old_tab[i]);
	xfree(old_tab);
}

int ft_free_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		;
	free(str);
	return(i);
}

char	*ft_strjoin_free2(char const *s1, char const *s2)
{
	char	*temp;
	size_t	index_dst;
	size_t	index_src;

	index_dst = 0;
	index_src = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (temp == 0)
		return (NULL);
	while (s1[index_dst] != '\0')
	{
		temp[index_dst] = s1[index_dst];
		index_dst++;
	}
	while (s2[index_src] != '\0')
	{
		temp[index_dst] = s2[index_src];
		index_dst++;
		index_src++;
	}
	temp[index_dst] = '\0';
//	xfree((void *)s1);
	xfree((void *)s2);
	return (temp);
}

int ft_isspace(char c)
{
	if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		return (0);
	return (1);
}