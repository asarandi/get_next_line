/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 12:10:14 by asarandi          #+#    #+#             */
/*   Updated: 2017/10/18 22:21:48 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>

char	*mem_increase(char *src, int existing, int additional)
{
	char	*dst;

	if ((dst = ft_memalloc(existing + additional)) == NULL)
		return (NULL);
	ft_memcpy(dst, src, existing);
	free(src);
	return (dst);
}

int	get_next_line(const int fd, char **line)
{
	static t_gnl	first;
	char	*m1;
	char	*m2;
	int		msize;
	int		r;
	char	c;
	int	eof;
	int rsize;
	char *ret;

	eof = 0;
	if ((fd == 1) || (fd == 2))
		return (-1);
	if ((first.fd == fd) && (first.mem))
	{
		m1 = first.mem;
		msize = first.size;
	}
	else
	{
		if ((read(fd, &c, 0)) == -1) //bad fd
			return (-1);
		if ((m1 = ft_memalloc(BUFF_SIZE)) == NULL) //malloc fail
			return (-1);
		if ((r = read(fd, m1, BUFF_SIZE)) == 0) //eof
		{
			free(m1); //8:37pm
			*line = NULL;
			return (0);
		}
		if (r < BUFF_SIZE)
			eof = 1;
		msize = BUFF_SIZE;
	}
	while ((m2 = ft_memchr(m1, '\n', msize)) == NULL)
	{
		if ((eof) && (m1[0]))
		{
			first.mem = 0;
			*line = m1;
			return (1);
		}
		else if ((eof) && (!m1[0]))
		{
			if (msize)
				free(m1);
			first.mem = 0;
			*line = NULL;
			return (0);
		}
		if ((m1 = mem_increase(m1, msize, BUFF_SIZE)) == NULL)
			return (-1);
		if ((r = read(fd, &m1[msize], BUFF_SIZE)) == 0)
			eof = 1;
		msize += BUFF_SIZE;
	}
	rsize = m2 - m1;
	if ((ret = ft_memalloc(rsize + 1)) == NULL)
		return (-1);
	*line = ft_memcpy(ret, m1, rsize);

	if ((first.mem = ft_memalloc(msize - rsize - 1)) == NULL)
		return (-1);
	ft_memcpy(first.mem, &m1[rsize + 1], msize - rsize - 1);
	first.size = msize - rsize - 1;
	first.fd = fd;
	free(m1);
	return (1);
}
