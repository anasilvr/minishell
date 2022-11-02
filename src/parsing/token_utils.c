#include "../../include/minishell.h"

int	tok_len(char *str, int len)
{
	int i;
	if (!str)
		return (0);
	i = 0; // handle dollar somewhere around here so it doesnt get split maybe?
	while (i < len)
	{
		if (is_set(str[i], METACHAR) || is_set(str[i], QUOTES))
		{
			if (i == 0 && (is_set(str[i], QUOTES)))
				i = (1 + lenght_til_match(str, str[i]));
			if (i == 0 && (is_set(str[i], REDIRCHAR) && is_set(str[i + 1], REDIRCHAR)))
				manage_meta(); // criar uma função pra lidar com multi metachars >> <<
			else if (i == 0)
				i = 1;
			break ;
		}
		i++;
	}
	return (i);
}
// https://www.notion.so/tchalifour91/Gestion-du-projet-826479dbb4bf46cdb4c42c87ab64fc36
// create function manage_meta to beter segment line and facilitate later verification.
//DO NOT FALL INTO THE TRAP OF DOING TOO MUCH TOO SOON.

int	lenght_til_match(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (is_set(str[i], &c))
		{
			if (!is_set(str[i + 1], WHITESPACE))
				i++;
			else
				break ;
		}
		i++;
	}
	return (i);
}

void	id_tokens(t_tok **list)
{
	t_tok *node;

	node = *list;
	while (node)
	{
		if (is_pipe(node->token)) // checks for | WITHOUT QUOTES
			node->type = PIPE;
//		else if (is_heredoc(node->token)) // checks for <<
//			node->type = HEREDOC;
//		else if (is_redir(node->token)) // isolated < >
//			node->type = INVALID;
		else
			node->type = WORD;
		node = node->next;
	}
}

bool	is_pipe(char *tok)
{
	if (!ft_strcmp(tok, "|"))
		return (true);
	else
		return (false);
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