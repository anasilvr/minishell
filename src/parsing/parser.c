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
	t_type	*io;

	io = ft_xcalloc(sizeof(t_type));
	data->cmd_lst = create_cmdlist(data);
	count_expand(data->cmd_lst, data->token);
	split_args(data->cmd_lst);
	//assign_flags(data->cmd_lst, data->token, io, expand);
	//instead of assign_flags, count_expand(), open_filefds() 
	//open files and assign fds
	// error check: is argv[0] of each node a valid command? (access call),
	//				is the arg related to a redirection a valid file? (open call)
	// the access call can be used to set a valid path since you'll have to use access with a path to check its validity.
	// when access ((path, F_OK | X_OK) == 0)), store this path at data.cmd_lst.path;
	// the open call will be used to set the fds
	xfree(io);
}


// void	assign_flags(t_cmd *cmd_lst, t_tok *token, t_type *io, bool *expand)
// {
// 	while (cmd_lst && token)
// 	{
// 		while (token)
// 		{
// 			check_flags(&token->type, io, expand);
// 			if (*expand)
// 			{
// 				cmd_lst->expand += 1;
// 				*expand = 0;
// 			}
// 			if (*io)
// 			{
// 				cmd_lst->io_flag = *io;
// 				*io = 0;
// 				token = token->next;
// 				break ;
// 			}
// 			token = token->next;
// 		}
// 		cmd_lst = cmd_lst->next;
// 	}
// }

// void	check_flags(t_type *toktype, t_type *io, bool *expand)
// {
// 	if (*toktype >= 2 && *toktype <= 6)
// 		*io = *toktype;
// 	if (*toktype == 8 || *toktype == 10)
// 		*expand = true;
// }
