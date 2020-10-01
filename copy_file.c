#include "cub3d.h"

void			*terminate(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char		*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1s2_len;
	unsigned int	i;
	char			*s3;

	if (!s1 || !s2)
		return (NULL);
	s1s2_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(s3 = malloc(s1s2_len + 1)))
		return (terminate((char **)&s1));
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	free((char *)s1);
	return (s3);
}

static char		*ft_emptystr(void)
{
	char	*s;

	if (!(s = malloc(1)))
		return (NULL);
	s[0] = '\0';
	return (s);
}

char			*copy_file(int fd)
{
	char	buf[2];
	char	*file;
	int		bytes;

	if (!(file = ft_emptystr()))
		return (NULL);
	while ((bytes = read(fd, buf, 1) > 0))
	{
		buf[bytes] = '\0';
		if (!(file = ft_strjoin(file, buf)))
			return (NULL);
	}
	return (file);
}
