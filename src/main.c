/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:40:36 by mtice             #+#    #+#             */
/*   Updated: 2025/08/21 21:00:59 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_all(t_data *all)
{
	all->c_envp = NULL;
	all->procs = NULL;
	all->info = NULL;
	all->tokens = NULL;
	all->total_proc = 0;
	all->return_val = 0;
}

//TODO: correct implementations of exit and env
//TODO: free after break from while loop
//TODO: implement history so that when "$?" is called the correct status can be displayed
int	main(int argc, char *argv[], char *envp[])
{
	t_data	all;
	char 	*input = NULL;

	if (argc > 1 || argv[0] == NULL || argv[0][0] == '\0')
		return (1);
	init_all(&all);
	if (find_envp(&all, envp))
		return (1); //TODO:free_all();
	while (42)
	{
		if (!isatty(fileno(stdin)))
			break;
		input = readline("minishell> ");
		if (!input || input[0] == '\0' || rl_on_new_line())
			continue ;
		add_history(input);
		if (!ft_strncmp("exit\0", input, 5))
			break ;
		else if (!ft_strncmp("$?\0", input, 3))
			printf("%d: command not found\n", all.return_val); //TODO: return the correct exit code
		else if (parsing(&all, input))
			continue ;
		 else if (execution(&all))
		 	continue ;
	}	
	rl_clear_history();
	//free_all();
	return (all.return_val);
}
