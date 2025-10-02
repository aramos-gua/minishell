/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:40:36 by mtice             #+#    #+#             */
/*   Updated: 2025/09/29 23:42:34 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = SA_RESTART;

void	pre_loop(int argc, t_data *all, char *argv[], char **envp)
{
	if (argc > 1)
		exit (126);
	(first_init(all), (void)argv);
	if (find_envp(all, envp))
		(ft_putendl_fd("minishell: envp could not be found", 2), exit(1));
}

//Testing purposes only
		// {
		// 	// break ;
		// 	char *temp;
		// 	temp = get_next_line(fileno(stdin));
		// 	input = ft_strtrim(temp, "\n");
		// 	free(temp);
		// }
int	main(int argc, char *argv[], char *envp[])
{
	t_data	all;
	char	*input;

	pre_loop(argc, &all, argv, envp);
	input = NULL;
	while (42)
	{
		(set_signals_interactive(&all), free_all(&all), init_all(&all));
		if (!isatty(fileno(stdin)))
		{
			break ;
			// char *temp;
			// temp = get_next_line(fileno(stdin));
			// input = ft_strtrim(temp, "\n");
			// free(temp);
		}
		else
			input = readline("minishell> ");
		if ((!input || rl_on_new_line()) && subtract_shlvl(&all))
		{
			if (all.shlvl)
				continue ;
			else
				break ;
		}
		add_history(input);
		if ((is_minishell(input) && ++(all.shlvl)) || \
			parsing(&all, input) || execution(&all, 0, 0, 0))
			continue ;
	}
	return (last_free(&all), all.return_val);
}
