#include "../../include/minishell.h"

static void find_match(t_data *data, int *i, bool *trigger, char *quote)
{
    while (data->input[*i])
    {
        if (data->input[*i] == *quote)
        {
            *trigger = false;
            *quote = 0;
            break ;
        }
    *i += 1;
    }
}

char *charjoinfree(char *s1, char c)
{
    char    *str;
    int     len;

    len = ft_strlen(s1);
    str = ft_calloc(len + 1, sizeof(char));
    len = 0;
	if (s1 == NULL)
	{
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
    while (s1[len])
    {
        str[len] = s1[len];
        len++;
    }
    str[len] = c;
    str[len + 1] = '\0';
    xfree((void *) s1);
    return (str);
}

static char *clean_empty_quotes(char *input)
{
	char	*tmp;
	int		i;
	int		q;

	if (input)
	{
		tmp = ft_xcalloc(1, 1);
		i = -1;
		q = 0;
		while (input[++i])
		{
			while (is_set(input[i], QUOTES))
			{
				q = (1 + length_til_match(input, input[i]));
				if (q == 2)
				{
					i++;
					q = 0;
					break ;
				}
				if (!is_set(input[i], QUOTES))
					break ;
				if (!input[i])
					break ;
				i++;
			}
			tmp = charjoinfree(tmp, input[i]);
		}
		tmp = charjoinfree(tmp, '\0');
		xfree(input);
	}
	return(tmp);
}

static int	valid_quotation(t_data *data)
{
	int		i;
	bool	trigger;
	char	quote;

	i = -1;
	trigger = false;
	quote = 0;
	while (data->input[++i])
	{
		if (data->input[i] == '\'' || data->input[i] == '\"')
		{
			quote = data->input[i];
			trigger = true;
			i++;
			find_match(data, &i, &trigger, &quote);
			if (!data->input[i])
				break ;
		}
	}
	if (trigger == true)
		return (1);
	else
		return (0);
}

int	check_syntax(t_tok **list)
{
	t_tok	*node;
	t_tok	*tail;

    node = *list;
    tail = get_lasttok(node);
    if (is_set(*node->token, "|") || is_set(*tail->token, METACHAR))
        return (1);
    while (node)
    {
        if (node->type >= 2 && node->type <= 6)
            if (node->next->type != 1 && \
            !(node->next->type >= 7 && node->next->type <= 10))
                return (1);
        node = node->next;
    }
    return (0);
}

//$? = 1 catchall for g eneral errors and unclosed quotes
//$? = 258 for syntax errors
void    lexer(t_data *data, char *input)
{
    if (!data)
        return ;
    if (!input || !*input)
        return ;
    g_status = valid_quotation(data);
    if (g_status)
    {
        data->syntax_err = 90;
        return ;
    }
 	data->input = clean_empty_quotes(input);
    data->token = tokenize(data, data->input);
    if (!data->token)
        return ;
    g_status = id_tokens(&data->token, data);
    if (g_status)
        return ;
    verify_dollartype(&data->token);
	printf("\033[1m\033[31m[At lexer.c]\nBEFORE TREAT LINE:\033[0m\n");
	print_toklist(data->token);
    treat_line(&data->token, data->envp_cp);
	printf("\033[1m\033[31mAFTER TREAT LINE:\033[0m\n");
	print_toklist(data->token);
    return ;
}

t_tok   *tokenize(t_data *data, char *str)
{
    t_tok   *lst;

    lst = NULL;
    skip_whitespaces(&str);
    while (*str)
    {
        data->token->toksize = tok_len(str, ft_strlen(str));
        addback_toklist(&lst, \
            new_toklist(ft_substr(str, 0, data->token->toksize)));
        str += data->token->toksize;
        skip_whitespaces(&str);
    }
    free_toklist(data->token);
    return (lst);
}
