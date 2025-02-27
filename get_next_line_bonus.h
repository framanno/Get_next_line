/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:27:38 by fmanno            #+#    #+#             */
/*   Updated: 2025/02/25 16:27:41 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 18
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*read_and_buffer(int fd, char *buff_data);
char	*extract_line(char *buff_data, char **leftover_data);
int		read_until_eol(int fd, char *temp_buffer, char **buff_data);
char	*get_full_line(char **buff_data);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strncpy(char *dest, char *src, int n);
int		ft_strlen(char *s);

#endif
