/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:04:56 by mtice             #+#    #+#             */
/*   Updated: 2025/07/03 18:43:37 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t			ft_stringlen(const char *s);
char			*ft_strchr2(const char *s, int c);
static void		theloop(int fd, char *buf, char **line, int eof);
static void		moreloop(int fd, char *buf, int *p, int *eof);
char			*get_next_line(int fd);

size_t	ft_stringlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}

char	*ft_strchr2(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	c = (char)c;
	while (p[i] != '\0')
	{
		if (p[i] == c)
			return (&p[i]);
		i++;
	}
	if (c == '\0')
		return (&p[i]);
	return (NULL);
}

static void	moreloop(int fd, char *buf, int *p, int *eof)
{
	*p = read(fd, buf, BUFFER_SIZE);
	if (*p != BUFFER_SIZE)
		*eof = 1;
	buf[*p] = '\0';
}

static void	theloop(int fd, char *buf, char **line, int eof)
{
	char	*temp;
	int		p;

	p = 0;
	while (42)
	{
		if (ft_strchr2(buf, '\n') != NULL)
		{
			temp = ft_trim(buf, '\n');
			*line = ft_strjoin2(*line, temp);
			p = ft_stringlen(temp);
			ft_memmove2(buf, buf + p, BUFFER_SIZE - p);
			while (p > 0)
				buf[BUFFER_SIZE - p--] = '\0';
			return (free(temp));
		}
		else if (ft_strchr2(buf, '\n') == NULL && eof == 1)
		{
			*line = ft_strjoin2(*line, buf);
			buf[0] = 4;
			return ;
		}
		*line = ft_strjoin2(*line, buf);
		moreloop(fd, buf, &p, &eof);
	}
}

char	*get_next_line(int fd)
{
	int			p;
	int			eof;
	char		*line;
	static char	buf[1024][BUFFER_SIZE + 1];

	p = 0;
	eof = 0;
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || line == NULL)
		return (free(line), NULL);
	line[0] = '\0';
	if (buf[fd][0] == '\0')
	{
		p = read(fd, buf[fd], BUFFER_SIZE);
		if (p == -1 || p == 0)
			return (free(line), NULL);
		else if (p != BUFFER_SIZE)
			eof = 1;
		buf[fd][p] = '\0';
	}
	if (buf[fd][0] == 4)
		return (free(line), NULL);
	theloop(fd, buf[fd], &line, eof);
	return (line);
}
