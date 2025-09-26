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

void	default_sigquit(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

static void	signal_heredoc(int signal)
{
	g_signal = signal;
	ft_putstr_fd("\nminishell>", 1);
}

void	set_signals_heredoc(t_data *all)
{
	struct	sigaction 	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_heredoc;
	sigaction(SIGINT, &act, NULL);
	if (g_signal == SIGINT)
		all->return_val = 130;
}

static void	signal_noninteractive(int signal)
{
	g_signal = signal;
}

void	set_signals_noninteractive(t_data *all)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = &signal_noninteractive;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	if (g_signal == SIGINT)
		all->return_val = 130;
	else if (g_signal == SIGQUIT)
		all->return_val = 131;
}

static void	signal_interactive(int signal)
{
	g_signal = signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_interactive(t_data *all)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_interactive;
	sigaction(SIGINT, &act, NULL);
	if (g_signal == SIGINT)
		all->return_val = 130;
}
