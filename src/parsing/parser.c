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

void split_args(t_cmd **cmd_lst, t_tok *token)
{
	t_cmd *lst;
	t_cmd *head;

	head = *cmd_lst;
	lst = *cmd_lst;

	int i = 1;
	while (lst && token)
	{
		lst->args = create_args(&token);
		i++;
		if (token && (token->type == PIPE))
			token = token->next;
		lst = lst->next;
	}
	*cmd_lst = head;
}

static int	redirect_creation(char *line, int type, int *i)
{
	char	*redirect_filename;
	int		filename_len;
	int		fd; //0 == fdin, 1 == fdout

	filename_len = first_word_len(&line[(*i)]);
	redirect_filename = ft_substr(&line[(*i)], 0, filename_len);
	fd = -2;
	if (type == 0)
		fd = open_to_read(redirect_filename, 0);
	else if (type == 1)
		fd = open_to_readwrite(redirect_filename,O_TRUNC);
	else if (type == 2)
		fd = open_to_readwrite(redirect_filename, O_APPEND);
	(*i) += filename_len;
	return (fd);
}

/* La fonction traite les redirections < , > et >> depuis la liste de tokens.
 * Elle permet l'ouverture des fichiers en leur attribuant chacun un fd qui
 * seront niché dans les différents nodes de la liste cmd_lst et retire les
 * nodes de la liste de tokens. Ainsi, lors de la création des arguments de la
 * liste de commandes, seul les commandes et leurs arguments seront présent.
 *
 * PROTOTYPE : void	redirect_subparsing(t_data *data);
 *
 * PARAMÈTRES : La fonction prend en paramètre la struct data de notre
 * programme.
 *
 * RETOUR : Elle ne retourne rien.
 *
 * DETAILS :
 */

t_tok	*redirect_subparsing(t_data *data)
{
	t_tok *r_token;

	r_token = get_first_tok(data->token);
	while (data->token != NULL)
	{
		if (data->token->type == PIPE)
		{
			data->cmd_lst = data->cmd_lst->next;
			data->token = data->token->next;
		}
		if (data->token->type == APPEND || data->token->type == REDIR_OUT || data->token->type == REDIR_IN)
		{
			if (data->token->type == APPEND) // >>
				data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, O_APPEND);
			else if (data->token->type == REDIR_OUT) // >
				data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, O_TRUNC);
			else if (data->token->type == REDIR_IN) // <
				data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, 0);
			delmidnode_toklist(data->token->next);
			delmidnode_toklist(data->token->next);
			if (data->token->next == NULL)
				r_token = get_first_tok(data->token);
		}
		data->token = data->token->next;
	}
	return (r_token);
}

// old
// void	redirect_subparsing(t_data *data)
// {
// 	while (data->token != NULL)
// 	{
// 		if (data->token->type == PIPE)
// 		{
// 			data->cmd_lst = data->cmd_lst->next;
// 			data->token = data->token->next;
// 		}
// 		else if (data->token->type == APPEND) // >>
// 		{
// 			data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, O_APPEND);
// 			delmidnode_toklist(data->token->next);
// 		}
// 		else if (data->token->type == REDIR_OUT) // >
// 		{
// 			data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, O_TRUNC);
// 			delmidnode_toklist(data->token->next);
// 		}
// 		else if (data->token->type == REDIR_IN) // <
// 		{
// 			data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, 0);
// 			delmidnode_toklist(data->token->next);
// 		}
// 		data->token = data->token->next;
// 	}
// 	if (data->token->next == NULL)
// 	data->token = get_first_tok(data->token);
// }

void	parser(t_data *data)
{
	data->cmd_lst = create_cmdlist(data);
	count_expand(data->cmd_lst, data->token);
	// Traitement des redirection
	data->token = redirect_subparsing(data);
	split_args(&data->cmd_lst, data->token);
	if (data->cmd_lst->filefd[0] == -1 || \
	(data->cmd_lst->filefd[1] == -1 && errno == EACCES))
	{
		perror("Minishell :");
	}
}

/*	argv[0] of each node a valid command? (access call),
	is the arg related to a redirection a valid file? (open call)
the access call can be used to set a valid path
since you'll have to use access with a path to check its validity.
when access ((path, F_OK | X_OK) == 0)), store this path at data.cmd_lst.path */