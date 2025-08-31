/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:54:03 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/21 12:39:06 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*get_process(t_token *list, int i)
{
	t_token	*current;
	t_token	*cmd;

	if (!list)
		return (NULL);
	current = list;
	while (current->process_nbr != i)
		current = current->next;
	cmd = get_cmd_node(current, i);
	return (cmd);
}

t_token	*get_cmd_node(t_token *list, int i)
{
	t_token	*current;

	if (!list)
		return (NULL);
	current = list;
	while ((current->type != COMMAND && current->builtin != 1) || current->process_nbr != i)
		current = current->next;
	return(current);
}

int	ft_lstsize(t_token *list, int proc)
{
	t_token	*current;
	int		i;

	i = 0;
	if (!list)
		return (0);
	current = list;
	while (1)
	{
		if (current->process_nbr == proc)
			i++;
		current = current->next;
		if (current == list)
			break ;
	}
	dprintf(2, "listsize is [%d]\n", i);
	return (i);
}

void	sh_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
