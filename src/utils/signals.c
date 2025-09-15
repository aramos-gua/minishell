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

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	signal_heredoc(int signal)
{
	g_signal = signal;
	ft_putstr_fd("\nminishell> ", 1);
}

void	set_signals_heredoc(void)
{
	struct	sigaction 	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_heredoc;
	sigaction(SIGINT, &act, NULL);
}

static void	signal_noninteractive(int signal)
{
	g_signal = signal;
	if (g_signal == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	set_signals_noninteractive()
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
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_interactive;
	sigaction(SIGINT, &act, NULL);
}
