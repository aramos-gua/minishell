/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:04:15 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 15:04:40 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBDFT_H
# define LIBDFT_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include "./ft_dprintf/ft_dprintf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Filter
size_t	dprintf_strlen(const char *s);

// Memory handling
void	*dprintf_memset(void *s, int c, size_t n);

// String actions
size_t	dprintf_strlcpy(char *dst, const char *src, size_t size);
int		dprintf_atoi(const char *nptr);
char	*ft_hxtoa(unsigned long n, int upp);
char	*dprintf_strjoin(char const *s1, char const *s2);
char	*ft_printf_itoa(int n);
char	*ft_printf_utoa(unsigned int n);
int		dprintf_toupper(int c);
size_t	dprintf_strlcat(char *dst, const char *src, size_t size);

// Visible output
int		dprintf_putchar(char c, int fd);
int		dprintf_putstr(char *s, int fd);
int		dprintf_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);
#endif
