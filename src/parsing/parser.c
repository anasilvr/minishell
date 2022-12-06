#include "../../include/minishell.h"

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
	bool	*expand;

	io = ft_xcalloc(sizeof(t_type));
	expand = ft_xcalloc(sizeof(bool));
	data->cmd_lst = create_cmdlist(data);
	assign_flags(data->cmd_lst, data->token, io, expand);
	split_args(data->cmd_lst);
	xfree(io);
	xfree(expand);
}

void	assign_flags(t_cmd *cmd_lst, t_tok *token, t_type *io, bool *expand)
{
	while (cmd_lst && token)
	{
		while (token)
		{
			check_flags(&token->type, io, expand);
			if (*expand)
			{
				cmd_lst->expand = *expand;
				*expand = 0;
			}
			if (*io)
			{
				cmd_lst->io_flag = *io;
				*io = 0;
				token = token->next;
				break ;
			}
			token = token->next;
		}
		cmd_lst = cmd_lst->next;
	}
}

void	check_flags(t_type *toktype, t_type *io, bool *expand)
{
	if (*toktype >= 2 && *toktype <= 6)
		*io = *toktype;
	if (*toktype == 8 || *toktype == 10)
		*expand = true;

}
