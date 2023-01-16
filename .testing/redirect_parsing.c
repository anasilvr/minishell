#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/libft/libft.h"

int	first_word_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != ' ') // Voir a ajouter si besoin d<autre whitespaces
	{
		len++;
		i++;
	}
	return (i);
}

int	main(void)
{
	char	*line = "echo bob > outfile.txt";
	char	*line_cpylen;
	int	len;

	printf("%s\n", line);
	len = first_word_len(line);
	printf("%d\n", len);
	line_cpylen = ft_substr(line, 0, first_word_len(line));
	printf("%s\n", line_cpylen);
	return (0);
}
