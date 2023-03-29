/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2023/03/16 11:20:04 by anarodri         ###   ########.fr       */
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

	if (!envp || !(*envp))
	{
		ft_putstr_fd("Error: ENVP missing. Please restart your terminal\
			 before trying again.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		ft_putstr_fd("Error: Program call doesn't support any arguments.\
			 Try again.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data = NULL;
	data = init_data(envp, data);
	stdio_cpy(data);
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
		if (data->tester == false)
			data->input = rl_gets();
		else if (data->tester == true)
			data->input = tester();
		if (!data->input)
			readline_exit(data);
		if (!data->syntax_err && !is_empty(data->input))
		{
			lexer(data, data->input);
			if (data->syntax_err || !data->token)
				break ;
			if (parser(data) == -1 && (data->syntax_err || !data->cmd_lst))
				break ;
			// printf("\033[1m\033[31m----------START OF CMDLIST_DETAILS----------\033[0m\n");
			// cmdlist_details(data->cmd_lst);
			// printf("\033[1m\033[31m----------END OF CMDLIST_DETAILS----------\033[0m\n");
			// printf("\t\033[1m\033[32m[Starting execution...]\033[0m\n");
//			printf("\033[1m\033[31m----------START OF CMDLIST_DETAILS----------\033[0m\n");
			cmdlist_details(data->cmd_lst);
//			printf("\033[1m\033[31m----------END OF CMDLIST_DETAILS----------\033[0m\n");
//			printf("\t\033[1m\033[32m[Starting execution...]\033[0m\n");
			if (data->cmd_lst->err != -1)
				execution_manager(data);
			// printf("\t\033[1m\033[32m[DONE! Starting reset...]\033[0m\n\n");
//			printf("\t\033[1m\033[32m[DONE! Starting reset...]\033[0m\n\n");
			reset(data);
		}
		if (data->syntax_err)
			err_msg(data);
		reset(data);
	}
//	reset(data);
	return ;
}
