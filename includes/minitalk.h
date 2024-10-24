/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:06:22 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/24 13:56:06 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

//# include </usr/include/signal.h>
//# include </usr/include/linux/signal.h>
//# include </usr/include/x86_64-linux-gnu/sys/signal.h>
//# include </usr/include/x86_64-linux-gnu/asm/signal.h>
# include <signal.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

# define MAX_RETRY 5

void	bin_to_char(int signum, char *c);
int		error(char *error_msg);

#endif
