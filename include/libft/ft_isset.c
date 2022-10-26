#include "libft.h"

int	ft_isset(const char c, const char *set)
{
	int	i;

	if (!c || !set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
