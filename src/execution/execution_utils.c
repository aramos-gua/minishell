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

t_token *get_process(t_token *list, int i)
{
  t_token *current;
  t_token *cmd;
  char    *i_str;

  i_str = ft_itoa(i);
  write(2, "get_process start\n", 18);
  write(2, i_str, 1);
  write(2, "\n", 1);
  if (!list)
    return (NULL);
  current = list;
  while (current->process_nbr != i)
    current = current->next;
  cmd = get_cmd_node(current, i);
  return (cmd);
}

t_token *get_cmd_node(t_token *list, int i)
{
  t_token *current;

  if (!list)
    return (NULL);
  dprintf(2, "get_cmd_node start\n");
  current = list;
  dprintf(2, "the type is: %d\n", current->type);
  while ((current->type != COMMAND && current->type != BUILTIN) || current->process_nbr != i)
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

