/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:10:31 by mtice             #+#    #+#             */
/*   Updated: 2025/03/10 16:04:44 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

//libraries to remove
# include <stdio.h>
# include <fcntl.h>

size_t	ft_stringlen(const char *s);
char	*ft_strchr2(const char *s, int c);
char	*get_next_line(int fd);

//utils
void	*ft_memmove2(void *dest, const void *src, size_t n);
char	*ft_trim(const char *s, char set);
char	*ft_strjoin2(const char *s1, const char *s2);

#endif
