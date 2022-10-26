#include "libft.h"

void	*xfree(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
