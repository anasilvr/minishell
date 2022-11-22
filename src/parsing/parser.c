#include "../../include/minishell.h"

// change get_cmdline to something that copies data.input while cheking the token until a pipe for the flags.
// the way we're doing right now makes it nearly impossible to format the whitespaces the right way.
void	parser(t_data *data)
{
	data->cmd_lst = create_cmdlist(data);
	assign_flags(data->cmd_lst, data->token);
}

void	assign_flags(t_cmd *cmd_lst, t_tok *token)
{
	t_type *io;
	bool *expand;

	io = ft_xcalloc(sizeof(t_type));
	expand = ft_xcalloc(sizeof(bool));
	if (!cmd_lst || !token)
		return ;
	while (cmd_lst)
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
