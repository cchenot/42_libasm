/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchenot <cchenot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:12:20 by cchenot           #+#    #+#             */
/*   Updated: 2020/05/05 15:33:02 by cchenot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define	TESTSTRLEN(X)		printf("str: %s // ft_strlen: %lu // strlen: %lu\n", X, ft_strlen(X), strlen(X))
#define	TESTSTRCMP(X, Y)	printf("s1: %s // s2: %s // ft_strcmp: %d // strcmp: %d\n", X, Y, ft_strcmp(X, Y), strcmp(X, Y))
#define TESTFTWRITE(X, Y)	printf("\nbuf: %s // count: %d // ft_write: %lu // errno: %d // strerror: %s\n", X, Y, ft_write(STDOUT_FILENO, X, Y), errno, strerror(errno));
#define TESTWRITE(X, Y)		printf("\nbuf: %s // count: %d // write: %lu // errno: %d // strerror: %s\n", X, Y, write(STDOUT_FILENO, X, Y), errno, strerror(errno));
#define TESTSTRDUP(X)		str = ft_strdup(X); printf("str = ft_strdup(\"%s\") // str: %s // errno: %d // strerror: %s\n", X, str, errno, strerror(errno)); free(str); str = NULL;

ssize_t ft_read(int fd, void *buf, size_t count);
ssize_t ft_write(int fd, void *buf, size_t count);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);

int		main()
{
	printf("----- Tests for the libasm project -----\n");

	printf("Testing ft_strlen:\n");
	TESTSTRLEN("");
	TESTSTRLEN("1");
	TESTSTRLEN("A");
	TESTSTRLEN("Bonjour!");
	TESTSTRLEN("0123456789");
	TESTSTRLEN("Bonjour! 0123456789");
	printf("\n");

	char s[1024] = {0};

	printf("Testing ft_strcpy with char s[1024] = {0}:\n");
	printf("ft_strcpy:\n");
	printf("Copying 'Bonjour!' // s: %s\n", ft_strcpy(s, "Bonjour!"));
	printf("Copying 'Bonjour 0123456789' // s: %s\n", ft_strcpy(s, "Bonjour 0123456789"));
	printf("Copying '0123456789' // s: %s\n", ft_strcpy(s, "0123456789"));
	printf("Copying '' // s: %s\n", ft_strcpy(s, ""));
	printf("\n");
	memset((char *)s, 0, sizeof(s));
	printf("strcpy:\n");
	printf("Copying 'Bonjour!' // s: %s\n", strcpy(s, "Bonjour!"));
	printf("Copying 'Bonjour 0123456789' // s: %s\n", strcpy(s, "Bonjour 0123456789"));
	printf("Copying '0123456789' // s: %s\n", strcpy(s, "0123456789"));
	printf("Copying '' // s: %s\n", strcpy(s, ""));
	printf("\n");

	printf("Testing ft_strcmp:\n");
	TESTSTRCMP("", "Bonjour!");
	TESTSTRCMP("Bonjour!", "");
	TESTSTRCMP("Bonjour! 0123456789", "Bonjour! 0123456789");
	TESTSTRCMP("", "");
	TESTSTRCMP("Bonjour!", "Salut!");
	TESTSTRCMP("Salut!", "Bonjour!");
	TESTSTRCMP("01234", "56789");
	printf("\n");

	int fd = 0;
	printf("Testing ft_write:\n");
	printf("--------------------\n");
	printf("ft_write:\n");
	TESTFTWRITE("Bonjour!", 2);
	TESTFTWRITE("Salut!", 7);
	TESTFTWRITE("A", 2);
	TESTFTWRITE("", 0);
	TESTFTWRITE("0123456789", 11);
	TESTFTWRITE("Bonjour 0123456789", 19);
	printf("--------------------\n");
	printf("write:\n");
	TESTWRITE("Bonjour!", 2);
	TESTWRITE("Salut!", 7);
	TESTWRITE("A", 2);
	TESTWRITE("", 0);
	TESTWRITE("0123456789", 11);
	TESTWRITE("Bonjour 0123456789", 19);
	printf("--------------------\n");
	printf("Testing ft_write and write with a negative fd:\n");
	errno = 0;
	printf("ft_write returns: %ld // errno: %d // strerror: %s\n", ft_write(-1, "Bonjour!", 9), errno, strerror(errno));
	errno = 0;
	printf("write returns: %ld // errno: %d // strerror: %s\n", write(-1, "Bonjour!", 9), errno, strerror(errno));
	printf("\n");

	fd = 0;
	char buffer[2048] = {0};
	long	r = 0;
	int c;

	if ((fd = open("./Makefile", O_RDONLY)) == -1)
	{
		printf("Error opening Makefile to test ft_read, please try again\n");
		return (-1);
	}
	printf("Testing ft_read:\n");
	printf("--------------------\n");
	printf("ft_read with ./Makefile, and buffer of 1024\n");
	r = ft_read(fd, buffer, 2047);
	printf("ft_read returned: %ld\n", r);
	buffer[r] = 0;
	printf("buffer:\n%s", buffer);
	if ((c = close(fd)) == 1)
	{
		printf("Close error\n");
		return (-1);
	}

	if ((fd = open("./Makefile", O_RDONLY)) == -1)
	{
		printf("Error opening Makefile to test read, please try again\n");
		return (-1);
	}
	printf("--------------------\n");
	printf("read with ./Makefile, and buffer of 1024\n");
	r = ft_read(fd, buffer, 2047);
	printf("read returned: %ld\n", r);
	buffer[r] = 0;
	printf("buffer:\n%s", buffer);
	if ((c = close(fd)) == 1)
	{
		printf("Close error\n");
		return (-1);
	}
	printf("--------------------\n");

	printf("Testing read and ft_read with a negative fd:\n");
	errno = 0;
	printf("ft_read returns: %ld // errno: %d // strerror: %s\n", ft_read(-1, buffer, 2047), errno, strerror(errno));
	errno = 0;
	printf("read returns: %ld // errno: %d // strerror: %s\n", read(-1, buffer, 2047), errno, strerror(errno));
	printf("Testing ft_read when reading from a directory\n");
	if ((fd = open("./testdir", O_RDONLY)) == -1)
	{
		printf("Open error with ./testdir, please try again\n");
		return (-1);
	}
	printf("ft_read returns: %ld // errno: %d // strerror: %s\n", ft_read(fd, buffer, 2047), errno, strerror(errno));
	if ((c = close(fd)) == 1)
	{
		printf("Close error\n");
		return (-1);
	}

	printf("read when reading from a directory\n");
	if ((fd = open("./testdir", O_RDONLY)) == -1)
	{
		printf("Open error with ./testdir, please try again\n");
		return (-1);
	}
	printf("read returns: %ld // errno: %d // strerror: %s\n", read(fd, buffer, 2047), errno, strerror(errno));
	if ((c = close(fd)) == 1)
	{
		printf("Close error\n");
		return (-1);
	}
	printf("\n");

	errno = 0;
	printf("Testing ft_strdup\n");
	char *str = 0;
	TESTSTRDUP("Salut!");
	TESTSTRDUP("");
	TESTSTRDUP("Bonjour 0123456789");
	printf("----- Thank you ! -----\n");
}
