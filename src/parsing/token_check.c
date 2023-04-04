/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:23:29 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/03 14:23:30 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir(char *tok)
{
	if (!ft_strcmp(tok, "|") && ft_strlen(tok) == 1)
		return (PIPE);
	else if (!ft_strcmp(tok, "<<") && ft_strlen(tok) == 2)
		return (HEREDOC);
	else if (!ft_strcmp(tok, ">") && ft_strlen(tok) == 1)
		return (REDIR_OUT);
	else if (!ft_strcmp(tok, "<") && ft_strlen(tok) == 1)
		return (REDIR_IN);
	else if (!ft_strcmp(tok, ">>") && ft_strlen(tok) == 2)
		return (APPEND);
	else
		return (0);
}

int	is_valid(char *tok)
{
	if (is_set(*tok, METACHAR))
		return (INVALID);
	else if (is_set(*tok, "$"))
		return (DOLLAR);
	else
		return (WORD);
}

static void	check_hidden_dollars(t_tok *token)
{
	int		len;

	if (!token->token)
		return ;
	len = length_til_match(token->token, token->token[0]);
	while (len)
	{
		if (token->token[len] == '$')
		{
			token->type = D_EXPAND;
			return ;
		}
		len--;
	}
	token->type = WORD;
}

static void	check_if_return(t_tok *token)
{
	int	len;

	if (!token->token)
		return ;
	len = ft_strlen(token->token);
	if (token->token[len - 1] == '?' && !(len % 2))
	{
		token->type = D_RETURN;
		return ;
	}
	token->type = D_LITERAL;
}

void	verify_dollartype(t_tok **list)
{
	t_tok	*node;

	node = *list;
	while (node)
	{
		if (node->type == DOLLAR)
		{
			if (ft_strlen (node->token) == 1)
				node->type = WORD;
			if (ft_strlen(node->token) >= 2)
			{
				if (is_set(node->token[1], QUOTES))
					check_hidden_dollars(node);
				else if (!ft_isalnum(node->token[1]))
					check_if_return(node);
				else
				node->type = D_EXPAND;
			}
		}
		node = node->next;
	}
	return ;
}
