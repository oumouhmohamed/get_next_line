/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mooumouh <mooumouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:01:14 by mooumouh          #+#    #+#             */
/*   Updated: 2024/12/08 20:10:03 by mooumouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read(int fd)
{
    char *buffer;
    char *result;
    char *temp;
    int bytes_read;

    result = NULL;
    buffer = malloc ((long) sizeof (char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        temp = ft_strjoin(result, buffer);
        free(result);
        result = temp;
        if (ft_strchr(buffer, '\n'))
            break ;
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    free(buffer);
    if (bytes_read < 0)
        return (free(result), NULL);
    return (result);
}

char	*ft_new_line(char *buffer, char checking_rest)
{
	char	*line;
	char	*newline_pos;
	size_t	line_length;

	if (!buffer)
		return (NULL);
	newline_pos = ft_strchr(buffer, '\n');
	if (!newline_pos && checking_rest)
		return (NULL);
	if (!newline_pos && !checking_rest)
		return (ft_strdup(buffer));
	line_length = newline_pos - buffer + 1;
	line = (char *)malloc(sizeof(char) * (line_length + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, line_length + 1);
	return (line);
}

void	ft_clear(char **rest)
{
	free(*rest);
	*rest = NULL;
}

char	*handle_rest(char **rest)
{
	char	*line;
	char	*temp;

	if (!*rest)
		return (NULL);
	line = ft_new_line(*rest, 1);
	if (line != NULL)
	{
		temp = *rest;
		*rest = ft_strdup(ft_strchr(*rest, '\n') + 1);
		if (!*rest)
			ft_clear(rest);
		free(temp);
	}
	return (line);
}

char *get_next_line(int fd)
{
    char *buffer;
    char *line;
    char *temp;
    static char *rest;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE > 2147483647)
        return (ft_clear(&rest), NULL);
    line = handle_rest(&rest);
    if (line)
        return (line);
    buffer = ft_read(fd);
    if (!buffer && ft_strlen(rest) > 0)
        return (line = rest, rest = NULL, line);
    else if (!buffer && ft_strlen(rest) == 0)
        return (ft_clear(&rest), NULL);
    temp = ft_new_line(buffer, 0);
    line = ft_strjoin(rest, temp);
    free(temp);
    temp = ft_strchr(buffer, '\n');
    if (temp)
        rest = ft_strdup(temp + 1);
    else
        ft_clear(&rest);
    free(buffer);
    return (line);
}