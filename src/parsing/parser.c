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

static void split_args(t_cmd *cmd_lst, t_tok *token)
{
	t_cmd *lst;
	t_cmd *head;

	head = cmd_lst;
	lst = cmd_lst;

	int i = 1;
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
	data->cmd_lst = create_cmdlist(data);
	count_expand(data->cmd_lst, data->token);
	if (redirect_subparsing(data) == -1)
		return (-1);
	heredoc_subparsing(data);
	// printf("\033[1m\033[31m[At parser.c]\nAFTER REDIRECTION:\033[0m\n");
	// print_toklist(data->token);
	split_args(data->cmd_lst, data->token);
	if (data->cmd_lst->filefd[0] == -1 || \
	(data->cmd_lst->filefd[1] == -1 && errno == EACCES))
	{
		perror("Minishell :");
	}
	return (0);
}

/*	argv[0] of each node a valid command? (access call),
	is the arg related to a redirection a valid file? (open call)
the access call can be used to set a valid path
since you'll have to use access with a path to check its validity.
when access ((path, F_OK | X_OK) == 0)), store this path at data.cmd_lst.path */