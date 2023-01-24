#include <fcntl.h>
#include <stdio.h>
// #include <readline/readline.h>
#include "../include/readline/readline.h"
#include "../include/libft/libft.h"
#include "/..doubly_linked_list/doubly_linked_list.h"


//il etablie un prompt si il y a le flag heredoc
//a chaque fois que read est call il doit y avoir un putstr d<un chevrons et un espace devant
// typedef struct s_hdoc
// {
// 	char	*the_line;
// 	struct s_hdoc	*next;
// 	struct s_hdoc	*previous;
// }t_hdoc

t_hdoc	*heredoc(char *delimiter)
{
	char	*content;
	char	*line;
	t_hdoc	*hd_struct;

	content = (char *) NULL;
	line = (char *) NULL;
	while (ft_strcmp(delimiter, line))
	{
		if (line)
		{
			xfree(line);
			//line = (char *) NULL;
		}
		line = readline("> ");
		line = ft_strjoin_free(line, "");
		hd_struct = ft_dllst_add_back(hd_struct, line);
	}
	return (hd_struct);
}

int	main(void)
{
	printf("%s\n", heredoc("EOF"));
}

// read(int fildes, void *buf, size_t nbyte);