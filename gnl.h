/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 12:11:19 by asarandi          #+#    #+#             */
/*   Updated: 2017/10/16 00:41:18 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 32

typedef	struct		s_gnl
{
	void			*mem;
	size_t			size;
	int				fd;
	int				eof;
	struct s_gnl	*next;
}					t_gnl;

typedef unsigned char	t_uc;

int	get_next_line(const int fd, char **line);

#endif
