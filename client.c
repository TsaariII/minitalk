/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:35:38 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/11 14:01:53 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	error(char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit (1);
}

static void ft_send(int pid, char c, int end)
{
	int bit;

	bit = 7;
	while (bit >= 0)
	{
		
	}
}

int main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				pid;
	char				*msg;

	if (argc != 3 || !argv[2])
		error("Wrong input");
	pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = ft_acker;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error("Fail");
	msg = argv[2];
	while (*msg)
		ft_send(pid, *msg++, 0);
	ft_send(pid, '\0', 1);
}
