#include "../../include/minishell.h"

void	readline_exit(t_data *data)
{
	clean_exit(data);
	printf("exit\n");
	exit(0);
}

void treat_line(t_tok **tok, char **env_cp)
{
    int i;
    char *r_line;
    char *r_var;
    t_tok *node;

    r_line = NULL;
    r_var = NULL;
    node = *tok;
    while (node != NULL)
    {
        i = 0;
        while (node->token[i] != '\0')
        {
            if (node->type != WORD && node->type != D_EXPAND)
                break ;
            if (node->token[i] == '$')
                r_var = dollar_handler(node->token, env_cp, &i);
            if (node->token[i] == '\'' && r_var == NULL)
                r_var = single_quotes_handler(node->token, &i);
            else if (node->token[i] == '"' && r_var == NULL)
                r_var = double_quote_handler(node->token, env_cp, &i);
            if (r_var != NULL && r_line == NULL)
                r_line = ft_strdup(r_var);
            else if (r_var != NULL && r_line != NULL)
                r_line = ft_strjoin_free(r_line, r_var);
            else if (r_var == NULL)
            {
                r_line = charjoinfree(r_line, node->token[i]);
                i++;
            }
            if (r_var != NULL)
                r_var = xfree(r_var);
        }
		if (node->type == WORD || node->type == D_EXPAND)
		{
			xfree(node->token);
       		printf("%s\n", r_line);
        	node->token = ft_strdup(r_line);
        	r_line = xfree(r_line);
		}
        node = node->next;
    }
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
