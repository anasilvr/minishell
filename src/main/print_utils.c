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
	lst = cmdlst;
	i = 0;
	while (lst)
	{
		j = -1;
		printf("\n\t[cmdline %d] %s\n", i, lst->cmdline);
		while (lst->args && lst->args[++j])
			printf("\t[arg %d] %s \n", j, lst->args[j]);
		printf("\t[path] %s\n", lst->path);
		printf("\t[err] %d\n", lst->err);
		printf("\t[expand] %d\n", lst->expand);
		printf("\t[io_flag] %d\n", lst->io_flag);
		printf("\t[prev] %p\n", lst->prev);
		printf("\t[next]  %p\n\n", lst->next);
		i++;
		lst = lst->next;
	}
}