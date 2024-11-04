/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:35:38 by nzharkev          #+#    #+#             */
/*   Updated: 2024/11/04 08:12:39 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/*
 * Global variable to keep track of acknowledgment signals (SIGUSR1)
 * from the server.
 * Declaring it as volatile tells the compiler not to optimize it out,
 * as it can change asynchronously due to signal handling.
 * sig_atomic_t ensures it is safe to modify in signal handlers.
 */

volatile sig_atomic_t	g_ack;

/*
 * Validates the given PID and checks that it is a valid, positive integer.
 * Also confirms that the PID belongs to an active process
 * by using the `kill` function.
 * If the PID is invalid, it calls error_msg to display an error.
 */

static void	validation(char *str, pid_t pid)
{
	int	i;

	i = 0;
	if (pid)
	{
		if (pid <= 0)
			error_msg("Invalid PID");
		if (kill(pid, 0) == -1)
			error_msg("Invalid PID");
	}
	if (*str)
	{
		while (str[i])
		{
			if (ft_isdigit((int)str[i]) == 0)
			{
				error_msg("Invalid PID");
				exit(1);
			}
			i++;
		}
	}
}

/*
 * Sends a single bit (1 or 0) as a signal (SIGUSR1 or SIGUSR2) to the server.
 * Waits for an acknowledgment from the server, retrying if necessary.
 * If acknowledgment is not received after MAX_RETRY attempts,
 * calls error_msg to display an error.
 */

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
	error_msg("THIS IS TOO MUCH STOP!");
}

/*
 * Sends each bit of the given character `c` to the server
 * by calling bits_and_pieces.
 * If `end` is set to 1 and `c` is the null terminator,
 * it prints "Done" to indicate the message completion.
 */

static void	messenger(int pid, char c, int end)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		bits_and_pieces(pid, (c >> bit) & 1);
		bit--;
	}
	if (end && !c)
		ft_printf("Done\n");
}

/*
 * Signal handler that sets g_ack to 1 when SIGUSR1 is received.
 * This function is used to acknowledge that the server has received a bit.
 */

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
}

/*
 * Main function that initializes the client, validates input arguments,
 * sets up the signal handler for acknowledgments,
 * and sends a message to the server.
 * The message is sent character by character,
 * with each bit communicated through signals.
 */

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				pid;
	char				*msg;
	int					i;

	i = 0;
	if (argc != 3 || !argv[2])
		error_msg("Wrong input. ");
	pid = ft_atoi(argv[1]);
	validation(argv[1], pid);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = ack_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_msg("Sigaction failed");
	msg = argv[2];
	while (*msg)
		messenger(pid, *msg++, 0);
	messenger(pid, '\0', 1);
	return (0);
}
