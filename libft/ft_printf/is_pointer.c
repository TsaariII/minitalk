/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:25:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/27 14:56:59 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_pointer(void *ptr, int *check)
{
	int	c;

	c = 0;
	c += is_str("0x", check);
	if (c == -1)
		return (-1);
	c += is_hex((unsigned long) ptr, 0, check);
	return (c);
}
