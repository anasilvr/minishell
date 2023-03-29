#include "../../include/minishell.h"

void	readline_exit(t_data *data)
{
	clean_exit(data);
	printf("exit\n");
	exit(0);
}

char	*charjoinfree(const char *s1, const char c)
{
	char	*r_str;
	int		len;
	int		i;

	if (!s1)
		len = 0;
	else
		len = ft_strlen(s1);
	i = -1;
	r_str = NULL;
	if (len < 1)
	{
		r_str = malloc(sizeof(char) * 2);
		r_str[0] = c;
		r_str[1] = '\0';
	}
	else if (len > 0)
	{
		r_str = malloc(sizeof(char) * (len + 2));
		while (s1[++i] != '\0')
			r_str[i] = s1[i];
		r_str[i] = c;
		r_str[i + 1] = '\0';
	}
	xfree((char*) s1);
	return (r_str);
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
//            printf("%s\n", r_var);
            if (r_var != NULL)
                r_var = xfree(r_var);
        }
		if (node->type == WORD || node->type == D_EXPAND || node->type == D_LITERAL)
		{
			xfree(node->token);
        	node->token = ft_strdup(r_line);
            if (node->token == NULL)
                node = delmidnode_toklist(node);
        	r_line = xfree(r_line);
		}
        node = node->next;
    }
}

char	*rl_gets(void)
{
	char	*line;
	char 	*r_line;

	line = (char *) NULL;
	line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
	if (line && *line)
		add_history(line);
	r_line = ft_strdup(line);
	xfree(line);
	return (r_line);
}
