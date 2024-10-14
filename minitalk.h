/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:06:22 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/11 14:04:43 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

//# include </usr/include/signal.h>
# include </usr/include/linux/signal.h>
//# include </usr/include/x86_64-linux-gnu/sys/signal.h>
//# include </usr/include/x86_64-linux-gnu/asm/signal.h>

# include <unistd.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

void	bit_to_char(int signum, char *c);

#endif
