#include <stdio.h>

static void	add(int *i)
{
	(*i) += 10;
}

int	main(void)
{
	int	i;

	i = 1;
	add(&i);
	printf("%d\n", i);
	return (0);
}