/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_timestamp.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:21:16 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 16:05:02 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CHECK_TIMESTAMP_H
# define	CHECK_TIMESTAMP_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

typedef	unsigned int	t_size;

typedef struct	s_list
{
	int				fd;
	int				flag_eof;
	t_size			buff_size;
	t_size			line_size;
	t_size			buff_indx;
	char			*buffer;
	struct s_list	*next;
}				t_lista;

int				get_next_line(int fd, char **line);
int				ft_read_fd(t_lista *elm, char **line);
int				ft_fill_line(t_lista *elm, char **line);
void			ft_clear_elm(t_lista **begin_list, t_lista *elm_to_del);
t_lista			*ft_create_elmem(int fd);
t_lista			*ft_push_front(t_lista **begin_list, int fd);
char			*ft_strncpy(char *dst, char *src, size_t len);
char			*ft_realloc_spe(char *src, size_t init_len, size_t add_len);
char			*ft_strncat(char *dst, char *src,
										size_t line_offset, size_t add_len);

#endif
