#include "../../include/minishell.h"

int	tok_len(char *str, int len)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		if (is_set(str[i], METACHAR)
			|| is_set(str[i], QUOTES)
			|| is_set(str[i], "$"))
		{
			if (i == 0 && ((is_set(str[i], QUOTES))))
				i = (1 + lenght_til_match(str, str[i]));
			if (i == 0 && (is_set(str[i], METACHAR)))
				i = (1 + lenght_til_set(str, WHITESPACE));
			if (i == 0 && (is_set(str[i], "$")))
				i = (1 + lenght_til_set(str, WHITESPACE));
			else if (i == 0)
				i = 1;
			break ;
		}
		i++;
	}
	return (i);
}
//ATTENTION WHILE CHECKING $: CHECK RAW INPUT FOR SPACES BETWEEN WORDS
// problema quando meu meta está ligado direto à uma letra qualquer.
// os metas em sequencia devem ficar juntos pra validação depois, mas devem se separar caso:
// encontrem espaços (OK) ou outro char não meta (KO)
// |a| == [0]=| [1]=a [2]=|
// atualmente, |a| == [0]=|a|

int	lenght_til_set(char *str, char *set)
{
	int	i;

	if (!str || !set)
		return (0);
	i = 1;
	while (str[i])
	{
		if (is_set(str[i], set) ||)
			break ;
		i++;
	}
	return (i);
}

int	lenght_til_match(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (is_set(str[i], &c) && is_set(str[i + 1], &c))
			i++;
		else if (is_set(str[i], &c))
			break ;
		i++;
	}
	return (i);
}

void	id_tokens(t_tok **list)
{
	t_tok	*node;

	node = *list;
	while (node)
	{
		if (is_redir(node->token)) // isolated < >
			node->type = is_redir(node->token);
		if (node->type == NOTSET)
			node->type = is_valid(node->token);
		node = node->next;
	}
}

int	is_valid(char *tok)
{
	printf("Gettinghere with %s\n", tok);
	return (0);
}

int	is_redir(char* tok)
{
	if (!ft_strcmp(tok, "|") && ft_strlen(tok) == 2)
		return (PIPE);
	else if (!ft_strcmp(tok, "<<") && ft_strlen(tok) == 3)
		return(HEREDOC);
	else if (!ft_strcmp(tok, ">") && ft_strlen(tok) == 2)
		return (REDIR_OUT);
	else if (!ft_strcmp(tok, "<") && ft_strlen(tok) == 2)
		return (REDIR_IN);
	else if (!ft_strcmp(tok, ">>") && ft_strlen(tok) == 3)
		return (APPEND);
	else
		return (0);
}

bool	is_envvar(char *tok)
{
	if (!ft_strcmp(tok, "$") && *(tok + 1) )
		return (true);
	else
		return (false);
}

/*bool	is_word(char *tok)
{
	bool	quoted;

	if ((is_set(*tok, QUOTES)))
		quoted = true;
	else
		quoted = false;

	while (*tok)
	{
		if(is_set(*tok, METACHAR))
	}
	return(false);
}*/