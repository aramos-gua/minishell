/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:19:45 by mtice             #+#    #+#             */
/*   Updated: 2025/09/11 14:49:34 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	ignore_sigquit(void)
// {
// 	struct sigaction	sa;
//
// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// }
//
// static void	signal_print_newline(int signal)
// {
// 	(void)signal;
// 	rl_on_new_line();
// }
//
// static void	signal_reset_prompt(int signal)
// {
// 	(void)signal;
// 	ft_putstr_fd("\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }
//
// void	set_signals_interactive(void)
// {
// 	struct sigaction sa;
//
// 	ignore_sigquit();
// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_handler = &signal_reset_prompt;
// 	sigaction(SIGINT, &sa, NULL);
// }
//
// void	set_signals_noninteractive(void)
// {
// 	struct sigaction sa;
//
// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_handler = &signal_print_newline;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }
