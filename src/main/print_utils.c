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

void	print_toklist(t_tok **list)
{
	t_tok	*node;
	int		i;

	node = *list;
	i = 0;
	while (node)
	{
		if (!node)
			return ;
		printf("token[%d] = %s \t\t type = %u\n", i, node->token, node->type);
		node = node->next;
		i++;
	}
}

void	print_cmdlines(t_cmd *list)
{
	t_cmd	*node;
	int		i;

	node = list;
	i = 0;
	while (node)
	{
		printf("cmdline[%d] = %s\n", i, node->cmdline);
		node = node->next;
		i++;
	}
	cmdlist_details(list);
	return ;
}

void	cmdlist_details(t_cmd *cmdlst)
{
	t_cmd	*lst;
	int		i;

	if (!cmdlst)
		return ;
	lst = cmdlst;
	i = 0;
	while (lst)
	{
		printf("\n\t[cmdline %d] %s\n", i, lst->cmdline);
		printf("\t[path] %s\n", lst->path);
		printf("\t[fds] %d %d\n", lst->fd[0], cmdlst->fd[1]);
		printf("\t[err] %d\n", lst->err);
		printf("\t[expand] %d\n", lst->expand);
		printf("\t[io_flag] %d\n", lst->io_flag);
		printf("\t[prev] %p\n", &lst->prev);
		printf("\t[next]  %p\n\n", &lst->next);
		i++;
		lst = lst->next;
	}
}
