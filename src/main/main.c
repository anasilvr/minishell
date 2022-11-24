
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2022/11/04 17:31:15 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	signal_handler(int sig)
{
	t_data *data;

	data = get_data();
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	//	if (!data->cmd_lst)
			rl_redisplay();
	}
}

static void	readline_exit(t_data *data)
{
	clean_exit(data);
	printf("exit\n");
	exit(0);
}

static void	err_msg(t_data *data)
{
	if (data->syntax_err == 1)
	{
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_QUOTES);
//		write(2, ERR_QUOTES, ft_strlen(ERR_QUOTES));
//		write(2, "\n", 1);
	}
	else if (data->syntax_err == 127)
	{
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_CMD);
//		write(2, s, ft_strlen(s));
//		write(2, ERR_CMD, ft_strlen(ERR_CMD));
//		write(2, "\n", 1);
	}
	else if (data->syntax_err == 258)
	{
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_SYNTAX);
//		write(2, ERR_SYNTAX, ft_strlen(ERR_SYNTAX));
//		write(2, s, ft_strlen(s));
//		write(2, "\n", 1);
	}
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
	argv = NULL;
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
			cmdlist_details(data->cmd_lst);
			execution(data);
			// while (data->cmd_lst != NULL)
			// {
			// 	builtins_checker(data, data->cmd_lst);
			// 	data->cmd_lst = data->cmd_lst->next;
			// }
			reset(data);
		}
		if (data->syntax_err)
			err_msg(data);
		reset(data);
	}
	return ;
}

char	*rl_gets(void)
{
	char	*line;

	line = (char *) NULL;
	line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
	if (line && *line)
		add_history(line);
	return (ft_strjoin_free(line, ""));
}

// TO DO: I'd like to print the token that created the error in the message error...