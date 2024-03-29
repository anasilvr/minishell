/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2023/04/25 15:09:46 by tchalifo         ###   ########.fr       */
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
	if (data->syntax_err == 128)
		printf("Error: %s\n", ERR_QUOTES);
	else if (data->syntax_err == 129)
		printf("Error: %s\n", ERR_TOK);
	else if (data->syntax_err == 258)
		printf("Error: %s\n", ERR_SYNTAX);
	else
		printf("Error\n");
	data->syntax_err = 0;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;

	(void) argv;
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
			g_status = lexer(data, data->input);
			if (data->syntax_err == 0 && data->cmd_lst && parser(data) != -1)
			{
				if (data->tester == true)
					cmdlist_details(data->cmd_lst);
				if (data->cmd_lst->err != -1)
					execution_manager(data);
			}
		}
		if (data->syntax_err)
			err_msg(data);
		reset(data);
	}
}
