/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:22:24 by naankour          #+#    #+#             */
/*   Updated: 2024/12/03 15:54:59 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffer, char *temp)
{
	int	r;

	while (!(ft_strchr(buffer, '\n')))
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r <= 0)
		{
			if (r == 0)
				break ;
			free (buffer);
			buffer = NULL;
			return (NULL);
		}
		temp[r] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
		{
			free (temp);
			return (NULL);
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(temp);
		free(buffer);
		return (NULL);
	}
	buffer = ft_read(fd, buffer, temp);
	free (temp);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_strdup(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}