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
//TODO: fix bug where two prompts are being printed after quitting non-interactive mode
//TODO: understand what kind of global variable to use
//TODO: implement for heredoc
volatile int			g_unblock_sigquit;

static void	signal_non_interactive(int signal)
{
	(void)signal;
	rl_on_new_line();
}

static void	signal_interactive(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	if (g_unblock_sigquit)
	{
		act.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &act, NULL);
		act.sa_handler = &signal_non_interactive;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
	else
	{
		act.sa_handler = &signal_interactive;
		sigaction(SIGINT, &act, NULL);
	}
}
