/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:44 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:58:46 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

int	ft_print_memory(void *addr)
{
	int				counter;
	unsigned long	address_in_dec;

	counter = 0;
	address_in_dec = (unsigned long) addr;
	if (addr == NULL)
		return (ft_putstr_fd(("(nil)"), 1));
	counter += ft_putstr_fd("0x", 1);
	counter += ft_print_hex(address_in_dec, 0);
	return (counter);
}
