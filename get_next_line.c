#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
/*
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
*/
char	*ft_realloc(char *s1, char *s2)
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

int		get_char(int fd, char **line, char *buf)
{
	int		ret;

	ret = read(fd, buf, BUFFER_SIZE - BUFFER_SIZE + 1);
	if (ret == 0)
		return (0);
	if (buf[0] == '\n')
		return (1);
	buf[1] = '\0';
	*line = ft_realloc(*line, buf);
	return (2);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFFER_SIZE - BUFFER_SIZE + 2];

	if (fd < 0 || !(*line = malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = '\0';
	if ((ret = read(fd, buf, BUFFER_SIZE - BUFFER_SIZE + 1)) == -1)
		return (-1);
	if (ret == 0)
		return (0);
	buf[1] = '\0';
	if (buf[0] == '\n')
		return (1);
	*line = ft_realloc(*line, buf);
	while((ret = get_char(fd, line, buf)) == 2)
		;
	return (ret);
}
/*
int main(int argc, const char *argv[])
{
//	int		fd = open(argv[1], O_RDONLY);
	char	*line = NULL;
	int		ret = 1;

	while (ret > 0)
	{
	ret = get_next_line(0, &line);
	printf("ret = %d\n", ret);
	}
	return 0;
}*/
