#include <stdio.h>
#include "../include/libft/libft.h"

char	*executable_extraction(char *line)
{
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	len = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0')
		{
			if (line[i] == '>' || (line[i] == '>' && line[i + 1] == '>') || line[i] == '<')
			{
				if (line[++i] == ' ')
					i++;
				break;
			}
			if (start == 0 && i != 0 && len < 1)
				start = i;
			len++;
			i++;
		}
		while (line[i] != '\0' && line[i++] != ' ')
			;
	}
	return (ft_strtrim(ft_substr(line, start, len), " "));
}

int	main(void)
{
	char	*line = {"< 12>ed thomas > 34 > 76"};

	printf ("%s\n", executable_extraction(line));
}
