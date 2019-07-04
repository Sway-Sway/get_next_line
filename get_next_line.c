/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkwayiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:45:12 by jkwayiba          #+#    #+#             */
/*   Updated: 2019/07/04 22:46:39 by jkwayiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int		read_chunk(int fd, char **buffer)
{
	char	*placeholder;
	char	temporary[BUFF_SIZE + 1];
	ssize_t	size;

	size = read(fd, temporary, BUFF_SIZE);
	if (size < 1)
		return (0);
	temporary[size] = '\0';
	placeholder = ft_strjoin(*buffer, temporary);
	ft_strdel(buffer);
	*buffer = ft_strdup(placeholder);
	ft_strdel(&placeholder);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char *str[255];
	char		buff[BUFF_SIZE + 1];
	int			ret;
	char		*ptr;
	char		*tmp;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	if (str[fd] == NULL)
		str[fd] = ft_strnew(0);
	while ((ptr = ft_strchr(str[fd],'\n')) == NULL)
	{
		ret = read_chunk(fd, &(str[fd]));
		if (ret == 0)
			break ;
	}
	if (ptr != NULL)
	{
		*ptr = '\0';
		*line = ft_strdup(str[fd]);
		tmp = ft_strdup(ptr + 1);
		ft_strdel(&(str[fd]));
		str[fd] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else if (ft_strlen(str[fd]) != 0)
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&(str[fd]));
	}
	else
		return (0);
	return (1);
}
