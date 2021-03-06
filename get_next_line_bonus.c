/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 14:31:58 by bepifani          #+#    #+#             */
/*   Updated: 2021/10/25 12:34:05 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	a = malloc(count * size);
	if (a == 0)
		return (0);
	ft_bzero(a, count * size);
	return (a);
}

char	*ft_end_str_from_buff(char *str)
{
	char	*s;
	int		a;
	int		b;

	b = 0;
	a = 0;
	if (!str)
		return (NULL);
	while (str[a] != '\n' && str[a] != '\0')
		a++;
	if (!str[a++])
	{
		ft_freestr(str);
		return (NULL);
	}
	s = ft_calloc(sizeof(char), (ft_strlen(str) - a + 1));
	if (!s)
		return (NULL);
	while (str[a] != '\0')
		s[b++] = str[a++];
	s[b] = '\0';
	ft_freestr(str);
	return (s);
}

char	*ft_one_str_to_n(char *str)
{
	char	*s;
	int		a;
	int		b;

	b = 0;
	a = 0;
	if (!str[a])
		return (NULL);
	while (str[a] != '\n' && str[a] != '\0')
		a++;
	s = ft_calloc(sizeof(char), (a + 1));
	if (!s)
		return (NULL);
	while (str[b] != '\n' && str[b] != '\0')
	{
		s[b] = str[b];
		b++;
	}
	if (str[b] == '\n')
	{
		s[b] = str[b];
		b++;
		s[b] = '\0';
	}
	return (s);
}

char	*ft_readfile(int fd, char *str)
{
	char	*buff;
	int		simvol;

	buff = ft_calloc(sizeof(char), (BUFFER_SIZE));
	if (!buff)
		return (NULL);
	simvol = 1;
	while (!ft_strchr(str, '\n') && simvol >= 0)
	{
		simvol = read (fd, buff, BUFFER_SIZE);
		if (simvol < 0)
		{
			ft_freestr(buff);
			return (NULL);
		}
		if (ft_strlen(buff) == 0 && simvol <= 1)
		{
			free (buff);
			return (str);
		}
		buff[simvol] = '\0';
		str = ft_strjoin(str, buff);
	}
	ft_freestr(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buf1;
	static char	*buf2[10300];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf2[fd] = ft_readfile(fd, buf2[fd]);
	if (buf2[fd] == NULL)
		return (NULL);
	buf1 = ft_one_str_to_n(buf2[fd]);
	buf2[fd] = ft_end_str_from_buff(buf2[fd]);
	return (buf1);
}
