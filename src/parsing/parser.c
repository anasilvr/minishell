#include "../../include/minishell.h"

static	void	count_expand(t_cmd *cmd_lst, t_tok *token)
{
	while (cmd_lst && token)
	{
		while (token)
		{
			if (token->type == 8 || token->type == 10)
				cmd_lst->expand += 1;
			if (token->type >= 2 && token->type <= 6)
			{
				cmd_lst->io_flag = token->type;
				token = token->next;
				break ;
			}
			token = token->next;
		}
		cmd_lst = cmd_lst->next;
	}
}

void	split_args(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		cmd_lst->args = ft_split(cmd_lst->cmdline, ' ');
		cmd_lst = cmd_lst->next;
	}
}

void	parser(t_data *data)
{
	data->cmd_lst = create_cmdlist(data);
	count_expand(data->cmd_lst, data->token);
	split_args(data->cmd_lst);
	//pre-open files and assign fds here! :)
	// error check: is argv[0] of each node a valid command? (access call),
	//				is the arg related to a redirection a valid file? (open call)
	// the access call can be used to set a valid path since you'll have to use access with a path to check its validity.
	// when access ((path, F_OK | X_OK) == 0)), store this path at data.cmd_lst.path;
}
