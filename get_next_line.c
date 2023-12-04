/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubattu <mrubattu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:26:05 by mrubattu          #+#    #+#             */
/*   Updated: 2023/10/10 16:38:37 by mrubattu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	buffer[BUFFER_SIZE + 1] = {'\0'};
	char		*line;
	int			bytesread;

	if (fd < 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!ft_strlen(buffer))
		{
			bytesread = read(fd, buffer, BUFFER_SIZE);
			if (bytesread == -1)
				return (free_if_bug(line, buffer), NULL);
			if (bytesread == 0)
				return (line);
		}
		line = cpy_to_n(line, buffer);
		buff_update(buffer);
		if (line && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	return (line);
}

/*#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int 	fd;
	char	*line;

	line = NULL;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	system("leaks a.out");
	close(fd);
	return (0);
}*/
