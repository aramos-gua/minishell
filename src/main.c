/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:40:36 by mtice             #+#    #+#             */
/*   Updated: 2025/09/14 22:06:52 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = SA_RESTART;

void	init_all(t_data *all)
{
	g_signal = SA_RESTART;
	all->procs = NULL;
	all->info = NULL;
	all->tokens = NULL;
	all->arr = NULL;
	all->total_proc = 0;
}
static void	first_init(t_data *all)
{
	all->shlvl = 1;
	all->return_val = 0;
	all->c_envp = NULL;
	all->c_exp = NULL;
	init_all(all);
}

void subtract_shlvl(t_data *all)
{
	all->shlvl--;
	if (all->shlvl > 2)
	{
		rl_clear_history();
		free_double_char(all->c_envp);
		if (all->c_exp)
			free_double_char(all->c_exp);
		find_envp(all, all->envp);
	}
}

void	add_shlvl(t_data *all)
{
	all->shlvl++;
}

static int	is_minishell(char *input)
{
	int	i;

	if (!ft_strncmp("./minishell\0", input, 12))
		return (1);
	else if (!ft_strncmp("./minishell", input, 11))
	{
		i = 11;
		while(ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

//TODO: correct implementations of exit and env
//TODO: allow execution to handle exit, and remember to free_all when exit is called
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
		set_signals_interactive();
		(free_all(&all), init_all(&all));
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
		if (!input || rl_on_new_line())//if (!input || input[0] == '\0' || rl_on_new_line())
		{
			subtract_shlvl(&all);
			if (all.shlvl)
				continue ;
			else
				break;
		}
		add_history(input);
		// if (!ft_strncmp("exit\0", input, 5)) //TODO: remove because it causes mem leaks
		// 	break ;
		if (is_minishell(input))
		{
			add_shlvl(&all);
			continue;
		}
		if (parsing(&all, input))
			continue ;
		if (execution(&all, 0, 0, 0))
			continue ;
		if (g_signal == SIGQUIT)
			all.return_val = 131;
	}	
	rl_clear_history();
  	free_double_char(all.c_envp);
	free_all(&all);
	if (all.c_exp)
		free_double_char(all.c_exp);
	return (all.return_val);
}
