/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubattu <mrubattu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:51 by mrubattu          #+#    #+#             */
/*   Updated: 2023/10/02 16:36:26 by mrubattu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_if_bug(char *line, char *buffer)
{
	free(line);
	ft_bzero(buffer, BUFFER_SIZE);
}

char	*cpy_to_n(char *line, char *buffer)
{
	char	*new;
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	i++;
	new = malloc(sizeof(char) * (ft_strlen(line) + i + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, line, ft_strlen(line) + 1);
	ft_strlcpy(&new[ft_strlen(line)], buffer, i + 1);
	if (line)
		free(line);
	return (new);
}

static void	buff_update(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		ft_bzero(buffer, BUFFER_SIZE);
	else
		ft_strlcpy(buffer, &buffer[i], ft_strlen(&buffer[i]) + 1);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1] = {{'\0'}};
	char		*line;
	int			bytesread;

	if (fd < 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!ft_strlen(buffer[fd]))
		{
			bytesread = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytesread == -1)
				return (free_if_bug(line, buffer[fd]), NULL);
			if (bytesread == 0)
				return (line);
		}
		line = cpy_to_n(line, buffer[fd]);
		buff_update(buffer[fd]);
		if (line && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	return (line);
}
