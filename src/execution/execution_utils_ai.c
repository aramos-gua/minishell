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

/* ========================================================================= */
/* OLD CODE (BEFORE FIX) - Potential infinite loop:

t_token *get_process(t_token *list, int i)
{
  t_token *current;
  t_token *cmd;

  if (!list)
    return (NULL);
  current = list;
  while (current->process_nbr != i)
    current = current->next;  // ❌ Could loop forever in circular list!
  cmd = get_cmd_node(current, i);
  return (cmd);
}

*/
/* ========================================================================= */

/* NEW CODE (AFTER FIX) - Safe circular list traversal: */
t_token *get_process(t_token *list, int i)
{
  t_token *current;
  t_token *cmd;
  t_token *start;

  /* REASONING: Defensive programming - handle NULL input */
  if (!list)
    return (NULL);
    
  /* REASONING: In circular doubly-linked list, list points to tail
   * So list->next is the actual head/first element */
  current = list->next;  /* Start at head of circular list */
  start = current;       /* Remember where we started */
  
  /* REASONING: Find first token belonging to process number i
   * Circular list traversal with safety check */
  while (current->process_nbr != i)
  {
    current = current->next;
    
    /* REASONING: Safety check prevents infinite loops
     * If we've gone full circle without finding process i,
     * it doesn't exist in the list */
    if (current == start)  /* ✅ FIXED: Completed full circle */
      return (NULL);       /* Process not found */
  }
  
  /* REASONING: Found a token for process i, but we need the COMMAND token
   * Process i might have multiple tokens: ["grep", ".c"] 
   * We need to find the one with type==COMMAND */
  cmd = get_cmd_node(current, i);
  return (cmd);
}

/* ========================================================================= */
/* OLD CODE (BEFORE FIX) - Dangerous infinite loop risk:

t_token *get_cmd_node(t_token *list, int i)
{
  t_token *current;

  if (!list)
    return (NULL);
  current = list;
  while ((current->type != COMMAND && current->builtin != 1) || current->process_nbr != i)
    current = current->next;  // ❌ No safety check! Could loop forever!
  return(current);
}

*/
/* ========================================================================= */

/* NEW CODE (AFTER FIX) - Safe do-while with circular check: */
t_token *get_cmd_node(t_token *list, int i)
{
  t_token *current;
  t_token *start;

  /* REASONING: Guard against NULL pointer dereference */
  if (!list)
    return (NULL);
    
  current = list;
  start = list;  /* Mark our starting position */
  
  /* REASONING: Use do-while because we want to check the starting node too
   * In a while loop, we might miss the first element */
  do  /* ✅ FIXED: Check current node first, then advance */
  {
    /* REASONING: Look for command token in the specific process
     * A command token has:
     * - type == COMMAND (from enum: COMMAND = 1)
     * - OR builtin == 1 (for built-in commands like cd, echo)
     * - AND belongs to process number i */
    if ((current->type == COMMAND || current->builtin == 1) && current->process_nbr == i)
      return (current);  /* Found the command token! */
      
    current = current->next;  /* Move to next token */
    
    /* REASONING: Continue until we've checked every token exactly once
     * In circular list, we're back at start when current == start */
  } while (current != start);  /* ✅ FIXED: Safe termination condition */
  
  /* REASONING: Completed full circle without finding command */
  return (NULL);  /* Command token not found in process i */
}

int ft_lstsize(t_token *list, int proc)
{
  t_token *current;
  int     i;

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
  return (i);
}

void  sh_putstr(char *str, int fd)
{
  int i;

  i = 0;
  while (str[i])
    write(fd, &str[i++], 1);
}
