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

void	split_args(t_cmd *cmd_lst, t_tok *token)
{
	while (cmd_lst && token)
	{
		cmd_lst->args = create_args(&token);
		if (token && (token->type == PIPE))
			token = token->next;
		cmd_lst = cmd_lst->next;
	}
}

void	parser(t_data *data)
{
	data->cmd_lst = create_cmdlist(data);
	count_expand(data->cmd_lst, data->token);
	split_args(data->cmd_lst, data->token);
	// heredoc handling here
	// if (data->cmd_lst->io_flag == HEREDOC)
	// 	write_heredoc(data->hd_delimiter);
	//pre-open files and assign fds here! :)
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