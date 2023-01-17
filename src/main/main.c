/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2023/01/17 15:24:15 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	err_msg(t_data *data)
{
	if (data->syntax_err == 1)
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_QUOTES);
	else if (data->syntax_err == 258)
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_SYNTAX);
	else if (data->syntax_err == 127)
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_CMD);
	else
		printf("[%d / %d] Error\n", g_status, data->syntax_err);
	data->syntax_err = 0;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;

	(void)argv;
	if (!envp || !(*envp))
	{
		ft_putstr_fd("Error: ENVP missing. \
		Please restart your terminal before trying again.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		ft_putstr_fd("Error: Program call doesn't support any flags or arguments.\
		Try again.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data = NULL;
	data = init_data(envp, data);
	print_intro();
	wtshell(data);
	clean_exit(data);
	exit (g_status);
}

void	wtshell(t_data *data)
{
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		data->input = rl_gets();
		if (!data->input)
			readline_exit(data);
		while (!data->syntax_err && !is_empty(data->input))
		{
			lexer(data, data->input);
			if (data->syntax_err || !data->token)
				break ;
			parser(data);
			if (data->syntax_err || !data->cmd_lst)
				break ;
			printf("----------START OF CMDLIST_DETAILS----------\n");
			cmdlist_details(data->cmd_lst);
			printf("----------END OF CMDLIST_DETAILS----------\n");
			if (data->cmd_lst->err != -1)
				execution_manager(data);
			reset(data);
		}
		if (data->syntax_err)
			err_msg(data);
		reset(data);
	}
	return ;
}
