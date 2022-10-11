/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2022/10/11 14:50:51 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;

	while (1)
	{
		line = rl_gets();
		if (!line)
			exit (0);
	}
	return (0);
}

char	*rl_gets(void)
{
	char *line;

	line = (char *) NULL;
	line = readline("WTShell\xF0\x9F\x90\x8C$ ");
	if (line && *line)
		add_history(line);
	return (ft_strjoin_free(line, "\n"));
}
