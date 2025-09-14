/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:13:31 by mtice             #+#    #+#             */
/*   Updated: 2025/09/14 21:47:42 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	handler(int sig_num, siginfo_t *info, void *context)
// {
// 	(void)sig_num;
// 	(void)context;
// 	g_signal = info->si_signo;
// }
//
// static void	setup_signal_handler(int sig_num)
// {
// 	struct sigaction	act;
//
// 	if (sig_num == SIGINT)
// 	{
// 		sigemptyset(&act.sa_mask);
// 		act.sa_sigaction = handler;
// 		act.sa_flags = SA_SIGINFO;
// 	}
// 	else if (sig_num == SIGQUIT)
// 	{
// 		ft_bzero(&act, sizeof(act));
// 		act.sa_handler = SIG_IGN;
// 	}
// 	sigaction(sig_num, &act, NULL);
// }
//
// int	set_signal_action(t_data *all)
// {
// 	(void)all;
// 	setup_signal_handler(SIGINT);
// 	setup_signal_handler(SIGQUIT);
// 	return (0);
// }


static void	signal_noninteractive(int signal)
{
	g_signal = signal;
	rl_on_new_line();
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_noninteractive;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

static void	signal_interactive(int signal)
{
	g_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_interactive;
	sigaction(SIGINT, &act, NULL);
}
