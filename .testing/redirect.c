#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int open_file()
{
	int fd1;

	fd1 = open("/Users/tchalifo/Documents/minishell/toto", 0 | O_CREAT, S_IRWXU);
	return (fd1);

}

int main(void)
{
	int fd;
	int newfd;

	fd = open_file();
	printf ("table size = %d\n", getdtablesize());
	dup2(fd, newfd);
	printf ("fd value %d\n", fd);
	printf ("newfd value %d", newfd);
}