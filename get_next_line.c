#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

size_t		ft_strlen(const char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*pos;

	if (!s)
		return (NULL);
	pos = (char *)s;
	while (*pos != c)
	{
		if (!*pos)
			return (0);
		pos++;
	}
	return (pos);
}

char *ft_realloc(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		k;

	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
	}
	k = 0;
	if (s2)
		while (s2[k])
			new[i++] = s2[k++];
	new[i] = '\0';
	free(s1);
	s1 = NULL;
	return (new);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFFER_SIZE - BUFFER_SIZE + 2];

	*line = NULL;
	if ((ret = read(fd, buf, BUFFER_SIZE - BUFFER_SIZE + 1)) == -1)
		return (-1);
	buf[1] = '\0';
	if (buf[0] == '\n')
		return (1);
	*line = ft_realloc(*line, buf);
	while((ret = read(fd, buf, BUFFER_SIZE - BUFFER_SIZE + 1) != 0  &&
			(buf[0] != '\n' && buf[0] != '\0')))
	{
		buf[1] = '\0';
		*line = ft_realloc(*line, buf);
	}
	buf[1] = '\0';
	if (buf[0] == '\0')
		return (0);
	else
		return (1);
}
/*
int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	*line;

	while (--ac)
	{
		av++;
		if ((fd = open(*av, O_RDONLY)) < 0)
			fd = 0;
		while ((ret = (get_next_line(fd, &line))) == 1)
		{
			printf("line : %s\n", line);
		//	free(line);
			printf("ret : %d\n", ret);
		}
	//	free(line);
		printf("line : %s\n", line);
		printf("%d\n", ret);
	}
	return (0);
}*/
