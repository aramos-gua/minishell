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
//TODO: understand what kind of global variable to use
//TODO: implement for heredoc

volatile sig_atomic_t	g_interactive = 1;
volatile sig_atomic_t	g_last_signal = 0;

static void	handler(int sig_num, siginfo_t *info, void *context)
{
	g_last_signal = info->si_signo;
	(void)sig_num;
	(void)context;
	if (g_last_signal == SIGINT && g_interactive == INTERACTIVE) //SIGINT and interactive mode
	{
		// printf("interactive\n");
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_last_signal == SIGINT && g_interactive == NON_INTERACTIVE) //SIGINT and non-interactive mode
	{
		// printf("non_interactive\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (g_last_signal == SIGINT && g_interactive == H_DOC)
	{
		//exit(1);
	}
}

static void	setup_signal_handler(int sig_num)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(sig_num, &act, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

int	set_signal_action(t_data *all)
{
	g_interactive = all->mode;
	g_interactive = H_DOC;
	dprintf(2, "mode:%d\n", g_interactive);
	struct sigaction	act;
	
	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (1);
	setup_signal_handler(SIGINT);
	if (g_last_signal == SIGINT && g_interactive == H_DOC)
		return (1);
	//g_last_signal = SA_RESTART;
	return (0);
}

// static void	signal_interactive(int signal)
// {
// 	(void)signal;
// 	printf("interactive\n");
// 	fflush(stdout);
// 	ft_putstr_fd("\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }
//
// static void	signal_non_interactive(int signal)
// {
// 	(void)signal;
// 	printf("non_interactive\n");
// 	fflush(stdout);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }
//
// static void	signal_heredoc(int signal)
// {
// 	(void)signal;
// 	//ft_putstr_fd("heredoc signals", 1);
// 	// ft_putstr_fd("\n", 0);
// 	// rl_replace_line("", 0);
// 	// rl_on_new_line();
// 	g_unblock_sigquit = 3;
// }
//
// int	set_signal_action(void)
// {
// 	struct sigaction	act;
//
// 	printf("sig_quit:%d\n", g_unblock_sigquit);
// 	ft_bzero(&act, sizeof(act));
// 	if (g_unblock_sigquit == 1) //unblocks SIGQUIT when non-interactive mode
// 	{
// 		act.sa_handler = &signal_non_interactive;
// 		sigaction(SIGINT, &act, NULL);
// 		sigaction(SIGQUIT, &act, NULL);
// 	}
// 	else if (g_unblock_sigquit == 2)
// 	{
// 		act.sa_handler = &signal_heredoc;
// 		sigaction(SIGINT, &act, NULL);
// 		//sigaction(SIGQUIT, &act, NULL);
// 	}
// 	else if (!g_unblock_sigquit) //blocks when in interactive mode
// 	{
// 		act.sa_handler = SIG_IGN; //blocks ctrl backslash
// 		sigaction(SIGQUIT, &act, NULL);
// 		act.sa_handler = &signal_interactive; //defines SIGINT behaviour
// 		sigaction(SIGINT, &act, NULL);
// 	}
// 	return (0);
// }
