/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:08:04 by tordner           #+#    #+#             */
/*   Updated: 2024/06/10 11:47:48 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buf(int fd, char *buf, char *back)
{
	int		r_value;
	char	*temp;

	r_value = 1;
	while (r_value != 0)
	{
		r_value = read(fd, buf, BUFFER_SIZE);
		if (r_value == -1)
			return (NULL);
		else if (r_value == 0)
			break ;
		buf[r_value] = '\0';
		if (back == NULL)
			back = ft_strdup("");
		temp = back;
		back = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (back);
}

char	*get_back(char *line)
{
	size_t	count;
	char	*back;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (NULL);
	back = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*back == '\0')
	{
		free(back);
		back = NULL;
	}
	line[count + 1] = '\0';
	return (back);
}

char	*get_next_line(int fd)
{
	static char	*back;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(back);
		back = NULL;
		return (NULL);
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	line = get_buf(fd, buf, back);
	free(buf);
	buf = NULL;
	if (line == NULL)
	{
		free(back);
		back = NULL;
		return (NULL);
	}
	back = get_back(line);
	return (line);
}
