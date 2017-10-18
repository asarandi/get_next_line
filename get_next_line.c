/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 12:10:14 by asarandi          #+#    #+#             */
/*   Updated: 2017/10/18 03:43:09 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*p;
	size_t			i;

	if ((p = malloc(size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (void *)(dest);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*m;

	i = 0;
	m = s;
	while (i < n)
	{
		if (m[i] == (unsigned char)c)
			return (void *)(&m[i]);
		i++;
	}
	return (NULL);
}


/* logic: read buff_size from fd,
** if buffer does not contain '\n', read another
** if '\n' is in the middle of buffer - allocate 2 mem buffers:
**      first will contain everything up to '\n',
**      second will contain everything after '\n' - store 2nd buffer for later
**

case 1 - '\n' within buffer - split buffer in two, return first part, keep 2nd part
case 2 - '\n' not in buffer, increase mem buffer, free first mem buffer; repeat till '\n' or EOF; goto case 1

need to create struct of file descriptiors, and buffers associated with fd
only one static variable, maybe list with pointer to next ?

typedef	struct	s_gnl
{
	void	*mem;
	size_t	mem_size;
	int		fd;
	int		eof;
}				t_gnl;




*/


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
	int		msize = 0;
	int		r;
	char	c;

	int	eof = 0;

	if ((fd == 1) || (fd == 2))
		return (-1);

	if ((fd != 0) && (first.fd == fd))
	{
		m1 = first.mem;
		msize = first.size;
	}
	else if ((fd == 0) && (first.size != 0))
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
			first.eof = 1;
			free(m1);
			*line = NULL;
			return (0);
		}
		msize = BUFF_SIZE;
	}
	// msize is size of memory
	// m1 is memory
	// r is number of bytes read
	
/*	if (m1[0] == '\n')
	{
		*line = NULL;
		msize -= 1;
		if (msize >= 1)
		{
			if ((m2 = ft_memalloc(msize)) == NULL)
			return (-1);
			ft_memcpy(m2, &m1[1], msize);
			free(m1);
			m1 = m2;
			first.mem = m1;
			first.size = msize;
			if (m1[0])
				return (1);
		}

		return (0);
	}
*/
	while ((m2 = ft_memchr(m1, '\n', msize)) == NULL)
	{
		if ((eof) && (m1[0]))
		{
			*line = m1;
			first.fd = 0;
			first.size = 0;
			return (1);
		}
		else if ((eof) && (!m1[0]))
		{
			first.fd = 0;
			first.size = 0;
			*line = NULL;
			return (0);
		}

		if ((m1 = mem_increase(m1, msize, BUFF_SIZE)) == NULL)
			return (-1);
		if ((r = read(fd, &m1[msize], BUFF_SIZE)) == 0)
			eof = 1;

		msize += BUFF_SIZE;
	}

	int	rsize = 0;
	char *ret;

	rsize = m2 - m1;

	if ((ret = ft_memalloc(rsize + 1)) == NULL)
		return (-1);
	*line = ft_memcpy(ret, m1, rsize);

	if ((first.mem = ft_memalloc(msize - rsize - 1)) == NULL)
		return (-1);
	first.mem = ft_memcpy(first.mem, &m1[rsize + 1], msize - rsize - 1);
	first.size = msize - rsize - 1;
	first.fd = fd;
	free(m1);
	return (1);
}
