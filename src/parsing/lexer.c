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

char *charjoinfree(const char *s1, const char c)
{
	char 	*r_str;
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
	s1 = xfree((char*)s1);
	return (r_str);
}

/*char *charjoinfree(const char *s1, const char c)
{
    char    *str;
    size_t     len;

	if (!s1)
		len = 0;
	else
	    len = ft_strlen(s1);
    str = ft_calloc(len + 2, sizeof(char));
    len = 0;
    while (s1[len])
    {
        str[len] = s1[len];
        len++;
    }
    str[len] = c;
    str[len + 1] = '\0';
   xfree((char *) s1);
    return (str);
}*/

static char *clean_empty_quotes(char *input)
{
	char	*tmp;
	int		i;
	char	q;

	tmp = ft_xcalloc(1, 1);
	i = -1;
	q = '\0';
	while (input[++i])
	{
		while (is_set(input[i], QUOTES))
		{
			q = input[i];
			if (input [i + 1] && input [i + 1] == q)
				i += 2 ;
			else
				break ;
		}
		if (!input[i])
			break ;
		tmp = charjoinfree(tmp, input[i]);
	}
	tmp = charjoinfree(tmp, '\0');
	xfree(input);
	return (tmp);
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
