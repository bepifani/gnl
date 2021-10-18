/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:38:47 by bepifani          #+#    #+#             */
/*   Updated: 2021/10/18 22:52:09 by bepifani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*end_str_from_buff(char *str)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	//i++;
	if (!str[i++])
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	s = malloc(sizeof(char) + (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	//i++;
	while (str[i] != '\0')
	{
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	if (str)
		free(str);
	str = NULL;
	return (s);
}

char	*str_to_n(char *str)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	s = malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	while (str[j] != '\n' && str[j])
	{
		s[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
	{
		s[j] = str[j];
		j++;
		s[j] = '\0';
	}
	return (s);
}

char	*readfile(int fd, char *str)
{
	char	*buff;
	int		simvol;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	simvol = 1;
	while (!ft_strchr(str, '\n') && simvol > 0)
	{
		simvol = read (fd, buff, BUFFER_SIZE);
		if (simvol < 0)
		{
			if (buff)
				free (buff);
			buff = NULL;
			return (NULL);
		}
		//buff[simvol] = '\0';
		// if (simvol == 0)
		// 	printf("%s\n", str);
		if (ft_strlen(buff) == 0 && simvol <= 1)
		{
			//printf("%s\n", str);
			if (buff)
				free (buff);
			buff = NULL;
			return (str);
		}
		buff[simvol] = '\0';
		str = ft_strjoin(str, buff);
	}
	if (buff)
		free (buff);
	buff = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buf1;
	static char	*buf2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf2 = readfile(fd, buf2);
	//printf("%s\n", buf2);
	if (buf2 == NULL)
		return (NULL);
	buf1 = str_to_n(buf2);
	buf2 = end_str_from_buff(buf2);
	printf("'%s'\n", buf1);
	return (buf1);
}

// int main(void)
// {
// 	char *line;
// 	int fd;

// 	fd = open("test.txt", O_RDONLY);
// 	while((line = get_next_line(fd)))
// 	{
// 		printf("'%s'\n", line);
// 	}
// }
