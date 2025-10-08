/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:13:31 by mtice             #+#    #+#             */
/*   Updated: 2025/09/27 14:45:03 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	signal_heredoc(int signal)
{
	g_signal = signal;
	ft_putstr_fd("\n", 1);
}

void	set_signals_heredoc(t_data *all)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_heredoc;
	sigaction(SIGINT, &act, NULL);
	if (g_signal == SIGINT)
		all->return_val = 130;
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

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
