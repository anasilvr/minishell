#include "../../include/minishell.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_cp[i++])
		xfree(data->envp_cp[i]);
	xfree(data->envp_cp);
	i = 0;
	while (data->path[i++])
		xfree(data->path[i]);
	xfree(data->path);
	xfree(data->input);
/*	xfree(data->cmd_list->ref);
	xfree(data->cmd_list->cmd);
	i = 0;
	while (data->cmd_list->cmd_args[i++])
		xfree(data->cmd_list->cmd_args[i]);
	xfree(data->cmd_list->cmd_args);
	xfree(data->cmd_list);*/
	xfree(data);
	exit(g_status);
}
