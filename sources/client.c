/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:35:38 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/25 14:26:39 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	g_ack;

int	error(char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit (1);
}

static void	bits_and_pieces(int pid, int bit)
{
	int	retry;

	retry = 0;
	while (retry <= MAX_RETRY)
	{
		if (bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		while (!g_ack && retry < MAX_RETRY)
		{
			usleep(100);
			retry++;
		}
		if (g_ack)
		{
			g_ack = 0;
			return ;
		}
	}
	error("THIS IS TOO MUCH> STOP!");
}

static void	messenger(int pid, char c, int end)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		bits_and_pieces(pid, (c >> bit) & 1);
		bit--;
	}
	if (end && c)
		ft_printf("Done\n");
}

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				pid;
	char				*msg;

	if (argc != 3 || !argv[2])
		error("Wrong input.");
	pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = ack_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error("Fail");
	msg = argv[2];
	while (*msg)
		messenger(pid, *msg++, 0);
	messenger(pid, '\0', 1);
	return (0);
}
