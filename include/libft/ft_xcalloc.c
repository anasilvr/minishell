#include "libft.h"

void	*ft_xcalloc(size_t mem_size)

{
	void	*ptr;

	ptr = malloc(mem_size);
	if (!ptr)
	{
		write(STDERR_FILENO, "Memory allocation error: Aborting.", 35);
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, (mem_size));
	return (ptr);
}