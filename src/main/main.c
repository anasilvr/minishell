
#include "../../include/minishell.h"

char	*rl_gets(void)
{
	char *line;

	line = (char *) NULL;
	line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
	if (line && *line)
		add_history(line);
	return (line);
//	return (ft_strjoin_free(line, "\n"));
}

int	main(int argc, char **argv, char **envp)
{
	char 	**line;
	char	**env;
	int		i;

	env = cpy_env(envp, 0);
	i = -1;
	line = malloc(sizeof(char) * 2);
	print_intro();
	while (1)
	{
		i = -1;
		line[0] = rl_gets();
		line[1] = NULL;
		if (!line)
			exit (0);
//		printf("%s", line[0]);
		line = ft_split(line[0], 0x20);
		env = builtins_checker(line, env);
//		while (line[++i] != NULL)
//			printf("%s\n", line[i]);
	}
	return (0);
}

