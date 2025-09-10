/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:35:57 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:36:02 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libdft.h"

# define FLAG_MINUS	1//00000001
# define FLAG_ZERO	2//00000010
# define FLAG_HASH	4//00000100
# define FLAG_PLUS	8//00001000
# define FLAG_SPACE	16//0010000

typedef struct s_format
{
	int			fd;
	char		pad;
	int			flags;
	int			width;
	int			precision;
	char		f_specifier;
	int			p_chars;
}	t_form;

int		dprintf_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);
void	bs(const char **str, t_form *format, va_list args);
void	parse_flags(const char **str, t_form *format);
void	parse_width(const char **str, t_form *format, va_list args);
void	parse_precision(const char **str, t_form *format, va_list args);
void	parse_specifier(const char **str, t_form *format);
void	apply_specifier(t_form *format, va_list args);
void	pbonus_c(char c, t_form *format);
void	pbonus_s(const char *str, t_form *format, va_list args);
void	pbonus_di(int n, t_form *format);
void	pbonus_u(unsigned int n, t_form *format);
void	print_hx(unsigned int n, t_form *format, int upp);
void	pbonus_p(void *address, t_form *format);
int		append_0(char **str, t_form *format);
#endif
