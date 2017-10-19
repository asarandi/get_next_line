/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 12:10:14 by asarandi          #+#    #+#             */
/*   Updated: 2017/10/19 03:15:13 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

char	*mem_increase(char *src, int cur, int add)
{
	char			*dst;

	if ((dst = ft_memalloc(cur + add)) == NULL)
		return (NULL);
	ft_memcpy(dst, src, cur);
	free(src);
	return (dst);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	first;
	char			*m1;
	char			*m2;
	int				eof;
	t_gnl			*gnl;

	eof = 0;
	if ((fd == 1) || (fd == 2))
		return (-1);
	gnl = &first;
	while ((gnl->fd != fd) && (gnl->mem) && (gnl->next))
		gnl = gnl->next;
	if ((gnl->fd == fd) && (gnl->mem))
		m1 = gnl->mem;
	else
	{
		if ((read(fd, &eof, 0)) == -1)
			return (-1);
		if ((m1 = ft_memalloc(BUFF_SIZE)) == NULL)
			return (-1);
		if ((read(fd, m1, BUFF_SIZE)) == 0)
		{
			free(m1);
			*line = NULL;
			return (0);
		}
		if ((gnl->mem) && (fd != gnl->fd))
		{
			gnl->next = ft_memalloc(sizeof(t_gnl));
			if (gnl->next == NULL)
				return (-1);
			gnl = gnl->next;
		}
		gnl->size = BUFF_SIZE;
		gnl->fd = fd;
	}
	while ((m2 = ft_memchr(m1, '\n', gnl->size)) == NULL)
	{
		if ((eof) && (m1[0]))
		{
			gnl->mem = 0;
			*line = m1;
			return (1);
		}
		else if ((eof) && (!m1[0]))
		{
			if (gnl->size)
				free(m1);
			gnl->mem = 0;
			*line = NULL;
			if (gnl != &first)
			{
				gnl = &first;
				while (gnl->next->fd != fd)
					gnl = gnl->next;
				free(gnl->next);
				gnl->next = NULL;
			}
			return (0);
		}
		if ((m1 = mem_increase(m1, gnl->size, BUFF_SIZE)) == NULL)
			return (-1);
		if ((read(gnl->fd, &m1[gnl->size], BUFF_SIZE)) == 0)
			eof = 1;
		gnl->size += BUFF_SIZE;
	}
	eof = (m2 - m1) + 1;
	if ((*line = ft_memalloc(eof)) == NULL)
		return (-1);
	ft_memcpy(*line, m1, eof - 1);
	if ((gnl->mem = ft_memalloc(gnl->size - eof)) == NULL)
		return (-1);
	ft_memcpy(gnl->mem, &m1[eof], gnl->size - eof);
	gnl->size -= eof;
	free(m1);
	return (1);
}
