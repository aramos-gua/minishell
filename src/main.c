/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:40:36 by mtice             #+#    #+#             */
/*   Updated: 2025/09/25 15:49:19 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = SA_RESTART;

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	t_data	all;
	char 	*input = NULL;

	if (argc > 1)
		return (126);
	first_init(&all);
	if (find_envp(&all, envp))
		return (ft_putendl_fd("minishell: envp could not be found", 2), 1);
	while (42)
	{
		(set_signals_interactive(&all), free_all(&all), init_all(&all));
		if (!isatty(fileno(stdin))) //TODO: change back
		{
			// break ;
			char *temp;
			temp = get_next_line(fileno(stdin));
			input = ft_strtrim(temp, "\n");
			free(temp);
		}
		else
			input = readline("minishell> ");
		if (!input || rl_on_new_line())
		{
			subtract_shlvl(&all);
			if (all.shlvl)
				continue ;
			else
				break;
		}
		add_history(input);
		if (is_minishell(input) && ++(all.shlvl))
			continue;
		if (parsing(&all, input))
			continue ;
		if (execution(&all, 0, 0, 0))
			continue ;
		// redir_errors(all.errors);
	}
	// rl_clear_history();
	//  	free_double_char(all.c_envp);
	// free_all(&all);
	// if (all.c_exp)
	// 	free_double_char(all.c_exp);
	return (last_free(&all), all.return_val);
}
