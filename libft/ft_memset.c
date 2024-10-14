/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:59:30 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 10:59:35 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *v, int value, size_t len)
{
	unsigned char	*p;
	unsigned char	n;

	n = (unsigned char)value;
	p = v;
	while (len > 0)
	{
		*p = n;
		p++;
		len--;
	}
	return (v);
}
