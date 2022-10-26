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
//			if (i == 0 && (is_set(str[i], REDIRCHAR) && is_set(str[i + 1], REDIRCHAR)))
//				manage_meta(); // criar uma função pra lidar com multi metachars >> << ou erro
			else if (i == 0)
				i = 1;
			break ;
		}
		i++;
	}
	return (i);
}

int	lenght_til_match(char *str, char c)
{
	int i;

	if (!str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (is_set(str[i], &c))
			break ;
		i++;
	}
	return (i);
}

/*void	id_tokens(t_tok **list)
{
	t_tok *node;

	node = *list;
	while (node)
	{
		if (is_builtin(node->token)) // strcmp with builtin's names
			node->type = BUILTIN;
		else if (is_cmd (node->token)) // absolute first node or first after a pipe + access
			node->type = CMD;
		else if (is_flag(node->token)) // if the node->prev was set as CMD and this one starts with -
			node->type = FLAG;
		else if (is_envvar(node->token)) // check for $
			node->type = ENVVAR;
		else if (is_pipe(node->token)) // checks for | WITHOUT QUOTES
			node->type = PIPE;
		else if (is_heredoc(node->token)) // checks for <<
			node->type = HEREDOC;
		else if (is_redir(node->token)) // isolated < >
			node->type = REDIR;
		else
			node->type = STR;
		node = node->next;
	}
}*/