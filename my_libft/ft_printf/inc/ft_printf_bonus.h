/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:06:20 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 15:33:47 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags
{
	int		left_adjust;
	int		plus;
	int		space;
	int		hash;
	int		zero;
	int		width;
	int		precision;
}			t_flags;

//printing functions
int		ft_print_m(t_flags *s_flags, const char *fmt, int i, va_list args);
void	ft_flags(t_flags *s_flags, const char *fmt, int i);
int		ft_print_b(const char *fmt, int i, va_list args);
int		ft_printf(const char *fmt, ...);

//mandatory
int		ft_print_c(char c);
int		ft_print_s(char *s);
int		ft_print_p(void *p, char type);
int		ft_print_di(int n);
int		ft_print_u(unsigned int u);
int		ft_print_x(unsigned long x, char type);

//bonus
int		ft_print_c_flags(char c, t_flags s_flags);
int		ft_print_s_flags(char *s, t_flags s_flags);
int		ft_print_p_flags(void *p, char type, t_flags s_flags);
int		ft_print_di_flags(int n, char type, t_flags s_flags);
int		ft_print_u_flags(unsigned int u, char type, t_flags s_flags);
int		ft_print_x_flags(unsigned int x, char type, t_flags s_flags);

//struct and utils
void	init_struct(t_flags *s_flags);
int		is_zero(const char *fmt);
void	find_wp(t_flags *s_flags, const char *fmt, int i);
void	flag_combo(t_flags *s_flags, va_list args, char type);
int		is_flag(char c);
int		is_spec(char c);
int		hps(char type, t_flags s_flags);
int		wpl(char type, char width, t_flags s_flags);
//int		ft_strlen(const char *fmt);
int		find_intlen(int n);
int		find_unintlen(unsigned int u);
int		find_hexlen(unsigned long x);
#endif
