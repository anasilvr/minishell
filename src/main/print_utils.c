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
		printf("token[%d] [type = %u] [ %s ]\n", i, list->type, list->token);
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
	t_cmd	*lst;
	int		i;
	int		j;

	if (!cmdlst)
		return ;
	i = 0;
	while (cmdlst)
	{
		j = 0;
		printf("----------START OF CMDLIST_DETAILS----------\n");
		printf("\n\t[cmdline %d] %s\n", i, cmdlst->cmdline);
		while (cmdlst->args[j])
		{
			printf("\t[arg %d] %s \n", j, cmdlst->args[j]);
			j++;
		}
		printf("\t[path] %s\n", cmdlst->path);
		printf("\t[err] %d\n", cmdlst->err);
		printf("\t[expand] %d\n", cmdlst->expand);
		printf("\t[io_flag] %d\n", cmdlst->io_flag);
		printf("\t[hd_delimiter] %s\n", cmdlst->hd_delimiter);
		printf("\t[prev] %p\n", cmdlst->prev);
		printf("\t[next]  %p\n\n", cmdlst->next);
		i++;
		cmdlst = cmdlst->next;
	}
	printf("----------END OF CMDLIST_DETAILS----------\n");
}
