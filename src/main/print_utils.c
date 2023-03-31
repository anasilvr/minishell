/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:54:20 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/31 16:54:22 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_intro(void)
{
	printf("\033[1;95m");
	printf("  █   █\n\
   █   █\n\
   █   █\n\
    ███            █████ 　　　\n\
  █▒░░█         ██▓▒▒▓██ ☆\n\
 █▒░●░░█    ██▓▒██▓▒▒▓█　　 ★\n\
 █▒░█░░██  ██▓▒██▓▒░▒▓█\n\
  ██▒░░░█ ██▓▒░██▓▒░▒▓█ 　　　★\n\
     █▒░░███▓▓▒░░ ████▓█\n\
    █▒▒░░░███▓▓▒▒░░░██ 　 ★★\n\
     █▒▒░░░██████████████\n\
      █▒▒▒▒▒▒▒▒▒▒▒▒▒▒░█\n\
       ██████████████████.•°*”˜҈.•°*”˜҈..•°*”˜҈.•°*”˜҈..•°*”˜҈.•°*”˜҈.\
What the shell!?\n\n");
	printf("\033[0m");
}

void	print_toklist(t_tok *list)
{
	int		i;

	i = 0;
	while (list)
	{
		printf("token[%d] [type = %u / len = %zu]\
		 [ %s ]\n", i, list->type, ft_strlen(list->token), list->token);
		list = list->next;
		i++;
	}
	printf("\n");
}

void	print_cmdlines(t_cmd *list)
{
	int		i;

	i = 0;
	while (list)
	{
		printf("cmdline[%d] = %s\n", i, list->cmdline);
		list = list->next;
		i++;
	}
	cmdlist_details(list);
	return ;
}

void	cmdlist_details(t_cmd *cmdlst)
{
	int		i;
	int		j;

	if (!cmdlst)
		return ;
	i = 0;
	while (cmdlst)
	{
		j = 0;
		printf("\n\t[cmdline %d] %s\n", i, cmdlst->cmdline);
		while (cmdlst->args && cmdlst->args[j])
		{
			printf("\t[arg %d] %s \n", j, cmdlst->args[j]);
			j++;
		}
		printf("\t[path] %s\n\t#filefd[0] %d\n", cmdlst->path, cmdlst->filefd[0]);
		printf("\t#filefd[1] %d\n", cmdlst->filefd[1]);
		printf("\t#pipefd[0] %d\n", cmdlst->pipefd[0]);
		printf("\t#pipefd[1] %d\n\t[err] %d\n", cmdlst->pipefd[1], cmdlst->err);
		printf("\t[expand] %d\n\t[io_flag] %d\n", cmdlst->expand, cmdlst->io_flag);
		printf("\t[hd_delimiter] %s\n", cmdlst->hd_delimiter);
		printf("\t[prev] %p\n\t[next]  %p\n\n", cmdlst->prev, cmdlst->next);
		i++;
		cmdlst = cmdlst->next;
	}
}
