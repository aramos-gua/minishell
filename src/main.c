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

//TODO: correct implementations of exit and env
//TODO: free after break from while loop
//TODO: implement history so that when "$?" is called the correct status can be displayed
int	main(int argc, char *argv[], char *envp[])
{
	t_data	all;
	char 	*input = NULL;

	(void)argc;
	(void)argv;
	if (find_envp(&all, envp))
		return (1); //TODO:free_all();
	while (42)
	{
		input = readline("minishell> ");
		// if (!input || input[0] == '\0')
		//  	printf("Goodbye!\n"), exit(1);
		if (!ft_strncmp("exit\0", input, 5))
			break;
		else if (!ft_strncmp("$?\0", input, 3))
			printf("%d: command not found\n", errno);
		else if (!ft_strncmp("env\0", input, 4))
			print_env(&all);
		else if (parsing(&all, input))
			continue;
		// else if (execution(&all))
		// 	continue ;
		//rl_add_history()
	}	
	//rl_clear_history();
	//free_all();
	return (0);
}
