/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:54:03 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/18 14:54:24 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token *get_process(t_token *list, int i)
{
  t_token *current;
  t_token *cmd;

  write(2, "get_process start\n", 18);
  if (!list)
    return (NULL);
  current = list;
  while (current->process_nbr != i)
    current = current->next;
  cmd = get_cmd_node(current);
  return (cmd);
}

t_token *get_cmd_node(t_token *list)
{
  t_token *current;

  if (!list)
    return (NULL);
  current = list;
  while (current->type != COMMAND)
    current = current->next;
  return(current);
}

int ft_lstsize(t_token *list)
{
  t_token *current;
  int     i;

  i = 1;
  if (!list)
    return (0);
  current = list;
  while (current->next != list)
  {
    i++;
    current = current->next;
  }
  return (i);
}

