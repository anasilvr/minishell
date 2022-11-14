#include <fcntl.h>
#include <stdio.h>

int open_file()
{
	int fd1;

	fd1 = open("/Users/tchalifo/Documents/minishell/toto", 0 | O_CREAT, S_IRWXU);
	return (fd1);

}

int main(void)
{
	int fd;

	fd = open_file();
	printf ("fd value %d", fd);
}