/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 12:10:14 by asarandi          #+#    #+#             */
/*   Updated: 2017/10/17 22:50:51 by asarandi         ###   ########.fr       */
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


static int	read_buff_size(int fd, char **buf)
{
	char	c;

	if ((read(fd, &c, 0)) == -1)
		return (-1);
	if ((*buf = ft_memalloc(BUFF_SIZE)) == NULL)
		return (-1);
	return (read(fd, *buf, BUFF_SIZE));
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

	if (fd == first.fd)
	{
		if (first.eof)
			return (0);

		m1 = first.mem;
		msize = first.size;
	}
	else
	{
		if ((r = read_buff_size(fd, &m1)) == -1)
		{
			*line = NULL;
			return (-1);
		}
		msize = BUFF_SIZE;
	}

	while ((m2 = ft_memchr(m1, '\n', msize)) == NULL)
	{
		m1 = mem_increase(m1, msize, BUFF_SIZE);
		r = read(fd, &m1[msize], BUFF_SIZE);
		if (r < 0)
		{
			*line = NULL;
			free(m1);
			return (r);
		}

		msize += r;
	}
	*line = ft_memcpy(ft_memalloc(m2 - m1 + 1), m1, m2 - m1);

	char *save = 0;
	msize = msize - (m2 - m1) - 1;

	if ((msize > 0) && (r == BUFF_SIZE))
	{
		save = ft_memcpy(ft_memalloc(msize), m2 + 1, msize);
		first.fd = fd;
		first.mem = save;
		first.size = msize;

	}
	free(m1);
	first.fd = fd;
	first.mem = save;
	first.size = msize;

	if ((msize >= 0) && (r == BUFF_SIZE))
		return (1);

	if (r < BUFF_SIZE)
	{
		first.eof = 1;
		return (1);
	}




	return (-1);
	


//	printf("%s", mem);

	

	return (0);
}
