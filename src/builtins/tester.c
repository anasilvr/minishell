#include "../../include/minishell.h"


static char *easy_gnl(int fd)
{
    char *line;
    char read_ret[2];

    line = NULL;
    while (read(fd, &read_ret, 1) != 0)
    {
        if (read_ret[0] == '\n')
            return (line);
		if (line == NULL)
			line = ft_strdup(read_ret);
		else
        	line = ft_strjoin_free(line, read_ret);
    }
    return (line);
}

char *tester()
{
    static int  fd;
    char        *r_gnl;

    r_gnl = NULL;
    if (fd == 0)
        fd = open("test.txt", O_RDONLY);
    sleep(1);
    if (!fd)
        return (r_gnl);
    r_gnl = easy_gnl(fd);
    if (r_gnl == NULL)
        close(fd);
    return (r_gnl);
}

void	man_yoyo_ma(char **instruct, t_data *data)
{
	int		fd;
    char	*r_gnl;

	r_gnl = NULL;
	if (instruct[1] == NULL)
		return ;
	if (ft_cmp_builtin(instruct[0], "man", 3) == 0 && ft_cmp_builtin(instruct[1], "yoyoma", 6) == 0)
	{
		data->cmd_lst->is_builtin = true;
		fd = open("yoyo_ma.txt", O_RDONLY);
		if (!fd)
			return ;
		r_gnl = easy_gnl(fd);
		while (r_gnl != NULL)
		{
			printf("%s\n", r_gnl);
    		r_gnl = easy_gnl(fd);
		}
    }
}