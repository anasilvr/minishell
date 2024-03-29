/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:45:43 by tchalifo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/24 09:41:50 by tchalifo         ###   ########.fr       */
=======
/*   Updated: 2023/04/21 15:37:58 by anarodri         ###   ########.fr       */
>>>>>>> d27766c5c36e6d3c4b4a8cc15950f72e8a055a20
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	count_expand(t_cmd *cmd_lst, t_tok *token)
{
	while (cmd_lst && token)
	{
		while (token && cmd_lst)
		{
			if (token->type == PIPE)
			{
				token = token->next;
				cmd_lst = cmd_lst->next;
			}
			if (token->type == 3)
			{
				cmd_lst->hd_delimiter = ft_strdup(token->next->token);
				token = token->next;
			}
			if ((token->type == 8 || token->type == 10))
				cmd_lst->expand += 1;
			if (token->type >= 2 && token->type <= 6)
				cmd_lst->io_flag = token->type;
			token = token->next;
		}
		cmd_lst = cmd_lst->next;
	}
}

static size_t	count_args(t_tok **token)
{
	size_t	nb_args;

	nb_args = 0;
	while (*token && (*token)->type != PIPE)
	{
		nb_args++;
		*token = (*token)->next;
	}
	return (nb_args);
}

char	**create_args(t_tok **token)
{
	t_tok		*tok;
	char		**args;
	size_t		nb_args;
	size_t		i;

	tok = *token;
	args = NULL;
	nb_args = 0;
	while (*token)
	{
		nb_args = count_args(token);
		args = ft_xcalloc((nb_args + 1), sizeof(char *));
		i = 0;
		while (i < nb_args)
		{
			args[i] = ft_strdup(tok->token);
			i++;
			tok = tok->next;
		}
		break ;
	}
	return (args);
}

static void	split_args(t_cmd *cmd_lst, t_tok *token)
{
	t_cmd	*lst;
	t_cmd	*head;
	int		i;

	head = cmd_lst;
	lst = cmd_lst;
	i = 1;
	while (lst && token)
	{
		lst->args = create_args(&token);
		i++;
		if (token && (token->type == PIPE))
			token = token->next;
		lst = lst->next;
	}
	cmd_lst = head;
}

int	parser(t_data *data)
{
	if (data->token && data->token->token)
	{
		data->cmd_lst = create_cmdlist(data);
		count_expand(data->cmd_lst, data->token);
		if (redirect_subparsing(data) == -1)
		{
			perror("WTS");
			g_status = errno;
			return (-1);
		}
		heredoc_subparsing(data);
		split_args(data->cmd_lst, data->token);
<<<<<<< HEAD
=======
		if (data->cmd_lst->filefd[0] == -1 || \
		(data->cmd_lst->filefd[1] == -1 && errno == EACCES))
		{
			perror("WTS: ");
		}
>>>>>>> d27766c5c36e6d3c4b4a8cc15950f72e8a055a20
		return (0);
	}
	return (-1);
}
