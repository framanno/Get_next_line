/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <fmanno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:25:39 by fmanno            #+#    #+#             */
/*   Updated: 2025/03/05 17:13:21 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buff_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff_data = read_and_buffer(fd, buff_data);
	if (!buff_data)
		return (NULL);
	line = get_full_line(&buff_data);
	if (!line)
	{
		free(buff_data);
		buff_data = NULL;
	}
	return (line);
}

char	*read_and_buffer(int fd, char *buff_data)
{
	char	*temp_buffer;
	int		total_bytes_read;

	temp_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	total_bytes_read = read_until_eol(fd, temp_buffer, &buff_data);
	free(temp_buffer);
	if (total_bytes_read == -1)
		return (NULL);
	else
		return (buff_data);
}

int	read_until_eol(int fd, char *temp_buffer, char **buff_data)
{
	int		bytes_read;
	char	*merged_data;

	bytes_read = 1;
	while (bytes_read > 0 && (!(*buff_data) || !ft_strchr(*buff_data, '\n')))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (-1);
		temp_buffer[bytes_read] = '\0';
		merged_data = ft_strjoin(*buff_data, temp_buffer);
		if (!merged_data)
			return (-1);
		*buff_data = merged_data;
	}
	return (bytes_read);
}

char	*extract_line(char *buff_data, char **leftover_data)
{
	char	*line;
	int		line_len;
	int		buff_len;

	line_len = 0;
	while (buff_data[line_len] && buff_data[line_len] != '\n')
		line_len++;
	if (buff_data[line_len] == '\n')
	{
		line_len += 1;
	}
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ft_strncpy(line, buff_data, line_len);
	line[line_len] = '\0';
	if (!buff_data)
		return (NULL);
	else
		buff_len = ft_strlen(buff_data);
	if (buff_len > line_len)
		*leftover_data = ft_strdup(buff_data + line_len);
	else
		*leftover_data = NULL;
	return (line);
}

char	*get_full_line(char **buff_data)
{
	char	*line;
	char	*leftover_data;

	if (!*buff_data || **buff_data == '\0')
		return (NULL);
	line = extract_line(*buff_data, &leftover_data);
	if (!line)
		return (NULL);
	free(*buff_data);
	*buff_data = leftover_data;
	return (line);
}
/*
int main(void)
{
    int fd;
    char *line;

    fd = open("fd0.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        return (1);
    }

    printf("===== LETTURA FILE =====\n");

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);

    printf("===== FINE DEL TEST =====\n");

    return (0);
}
*/