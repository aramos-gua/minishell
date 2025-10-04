/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:57:22 by mtice             #+#    #+#             */
/*   Updated: 2025/08/11 08:52:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_prev_c(char *prev_c, char input_i, char *input, int i)
{
	if ((*prev_c == '<' && input_i == '>')
		|| (*prev_c == '<' && input_i == '<' && ft_isspace(input[i - 1])))
		return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<'", 2), 1);
	else if ((*prev_c == '>' && input_i == '<')
		|| (*prev_c == '>' && input_i == '>' && ft_isspace(input[i - 1])))
		return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
	*prev_c = input_i;
	return (0);
}

//-----------------------------------------------------------------------------
//processes the raw input before it can be broken down into processes
//looks for syntax errors: invalid quotes, pipes, expansions, redirections
int	input_check(char *input)
{
	int		i;
	char	prev_c;

	i = 0;
	prev_c = '\0';
	while (input[i] != '\0')
	{
		while (ft_isspace(input[i]))
			i++;
		if (check_prev_c(&prev_c, input[i], input, i))
			return (1);
		if ((input[i] == '\'' || input[i] == '"') && syntax_quotes(input, &i))
			return (1);
		else if (input[i] == '|' && syntax_multiple_pipes(input, &i))
			return (1);
		else if (input[i] == '$' && syntax_expansion(input, &i))
			return (1);
		else if (input[i] == '<' && syntax_re_in(input, &i))
			return (1);
		else if (input[i] == '>' && syntax_re_out(input, &i))
			return (1);
		if (input[i] != '\0')
			i++;
	}
	return (0);
}
