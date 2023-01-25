#include "../../include/minishell.h"

void	readline_exit(t_data *data)
{
	clean_exit(data);
	printf("exit\n");
	exit(0);
}

char *treat_line(char *line, char **env_cp)
{
    int i;
    char *r_line;
    char *r_var;

    i = -1;
    r_line = NULL;
    r_var = NULL;
    while (line[++i] != '\0')
    {
        if (line[i] == '$')
            r_var = dollar_handler(line, env_cp, &i);
        if (line[i] == '\'')
            r_var = single_quotes_handler(line, &i);
		else if (line[i] == '"')
			r_var = double_quote_handler(line, env_cp, &i);
        if (r_var != NULL && r_line == NULL)
            r_line = ft_strdup(r_var);
        else if (r_var != NULL && r_line != NULL)
            r_line = ft_strjoin_free(r_line, r_var);
		else if (r_var == NULL)
			r_line = charjoinfree(r_line, line[i]);
		if (r_var != NULL)
			r_var = xfree(r_var);
    }
    printf("%s\n", r_line);
    return (r_line);
}

char	*rl_gets(char **env_cp)
{
	char	*line;

	line = (char *) NULL;
	line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
	if (line && *line)
		add_history(line);
	return (ft_strjoin_free(line, ""));
}
