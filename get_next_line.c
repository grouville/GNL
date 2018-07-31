/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/10 15:52:47 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/10 15:52:52 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int		ft_stock2line(char **line, char *(*stock)[SZ], int fd)
{
	int		len;
	char	*tmp;

	if (ft_strchr((*stock)[fd], '\n'))
	{
		len = ft_strchr((*stock)[fd], '\n') - (*stock)[fd];
		free(line[0]);
		line[0] = ft_strsub((*stock)[fd], 0, len);
		tmp = (*stock)[fd];
		(*stock)[fd] = ft_strdup(ft_strchr(tmp, '\n') + 1);
		free(tmp);
		return (1);
	}
	free(line[0]);
	line[0] = ft_strdup((*stock)[fd]);
	free((*stock)[fd]);
	(*stock)[fd] = NULL;
	return (0);
}

static int		ft_read_fd(char *str, char **line, int fd, char *(*stock)[SZ])
{
	int		ret;
	char	*tmp;
	int		len;

	ret = 0;
	while ((ret = read(fd, str, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		str[ret] = '\0';
		tmp = line[0];
		line[0] = ft_strjoin(tmp, str);
		free(tmp);
		if (ft_strchr(line[0], '\n') != NULL)
		{
			len = ft_strchr(line[0], '\n') - line[0];
			(*stock)[fd] = ft_strdup(line[0] + len + 1);
			tmp = ft_strdup(line[0]);
			free(line[0]);
			line[0] = ft_strsub(tmp, 0, len);
			free(tmp);
			break ;
		}
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char		*stock[SZ];
	char			*str;
	int				ret;

	if ((fd < 0 || fd > (SZ - 1)) || !line || BUFF_SIZE < 1)
		return (-1);
	line[0] = ft_strnew(BUFF_SIZE);
	if (stock[fd] != NULL)
	{
		if (ft_stock2line(&line[0], &stock, fd))
			return (1);
	}
	str = ft_strnew(BUFF_SIZE);
	if ((ret = ft_read_fd(str, &line[0], fd, &stock)) == -1)
		return (-1);
	free(str);
	if (ret == 0 && ft_strlen(line[0]) == 0)
	{
		free(stock[fd]);
		free(line[0]);
		return (0);
	}
	return (1);
}
