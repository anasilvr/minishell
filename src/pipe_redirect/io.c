#include "../../include/minishell.h"

void	stdio_cpy(t_data *prog_data)
{
	prog_data->stdio[0] = dup(0);
	prog_data->stdio[1] = dup(1);
	prog_data->stdio[2] = dup(2);

}

void	reset_stdio(t_data *prog_data)
{
	dup2(prog_data->stdio[0], 0);
	close(prog_data->stdio[0]);
	prog_data->stdio[0] = dup(0);
	dup2(prog_data->stdio[1], 1);
	close(prog_data->stdio[1]);
	prog_data->stdio[1] = dup(1);
	dup2(prog_data->stdio[2], 3);
	close(prog_data->stdio[2]);
	prog_data->stdio[2] = dup(3);
}

t_cmd *goto_lastnode(t_cmd *cmd_lst)
{
	while (cmd_lst->next != NULL)
		cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

t_cmd *goto_firstnode(t_cmd *cmd_lst)
{
	while (cmd_lst->prev != NULL)
		cmd_lst = cmd_lst->prev;
	return (cmd_lst);
}

void	redir_manager(t_data *prog_data)
{
	// if (prog_data->cmd_lst->io_flag == 3) // HEREDOC
	// {
	// 	dup2()
	// }
	while (prog_data->cmd_lst != NULL)
	{
		if (prog_data->cmd_lst->io_flag == 4) // Redir_in
		{
			if (prog_data->cmd_lst->next == NULL)
			{
				prog_data->cmd_lst = goto_firstnode(prog_data->cmd_lst);
			}
			dup2(prog_data->cmd_lst->next->filefd[0], 0);
			close(prog_data->cmd_lst->filefd[0]);
		}
		if (prog_data->cmd_lst->io_flag == 5 || prog_data->cmd_lst->io_flag == 6) // Redir_out
		{
			if (prog_data->cmd_lst->prev == NULL)
				dup2(prog_data->cmd_lst->filefd[1], 1);
			else
				dup2(prog_data->cmd_lst->filefd[1], 1);
			close(prog_data->cmd_lst->filefd[1]);
		}
		prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
}

// echo bonjour | cat