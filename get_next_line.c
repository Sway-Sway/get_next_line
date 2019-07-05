/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkwayiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:45:12 by jkwayiba          #+#    #+#             */
/*   Updated: 2019/07/05 17:17:21 by jkwayiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_chunk(int fd, char **buffer)
{
	char	*placeholder;
	char	temporary[BUFF_SIZE + 1];
	ssize_t	size;
	int		ret;
	char	*ptr;

	while ((ptr = ft_strchr(*buffer, '\n')) == NULL)
	{
		size = read(fd, temporary, BUFF_SIZE);
		if (size < 1)
			return (NULL);
		temporary[size] = '\0';
		placeholder = ft_strjoin(*buffer, temporary);
		ft_strdel(buffer);
		*buffer = ft_strdup(placeholder);
		ft_strdel(&placeholder);
	}
	return (ptr);
}

char	*ft_strdupdel(char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	ft_strdel(str);
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static char *str[255];
	char		buff[BUFF_SIZE + 1];
	char		*ptr;
	char		*tmp;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	if (str[fd] == NULL)
		str[fd] = ft_strnew(0);
	ptr = read_chunk(fd, &(str[fd]));
	if (ptr != NULL)
	{
		*ptr = '\0';
		tmp = ft_strdup(ptr + 1);
		*line = ft_strdupdel(&str[fd]);
		str[fd] = ft_strdupdel(&tmp);
	}
	else if (ft_strlen(str[fd]) != 0)
		*line = ft_strdupdel(line);
	else
		return (0);
	return (1);
}
