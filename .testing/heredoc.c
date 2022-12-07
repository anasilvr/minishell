#include <fcntl.h>
#include <stdio.h>
// #include <readline/readline.h>
#include "../include/readline/readline.h"
#include "../include/libft/libft.h"


//il etablie un prompt si il y a le flag heredoc
//a chaque fois que read est call il doit y avoir un putstr d<un chevrons et un espace devant

char	*heredoc(char *delimiter)
{
	char	*content;
	char	*line;

	content = (char *) NULL;
	line = (char *) NULL;
	while (ft_strcmp(delimiter, line))
	{
		if (line)
		{
			free(line);
			line = (char *) NULL;
		}
		line = readline("> ");
		line = ft_strjoin_free(line, "");
		//ft_strjoin(content, line); // Pas bon uiliser une liste pour feed les lines ! puis avec gnl lire les lignes et envoyer sur input descriptore standard
	}
	return (content);
}

int	main(void)
{
	printf("%s\n", heredoc("EOF"));
}

// read(int fildes, void *buf, size_t nbyte);