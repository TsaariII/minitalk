/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:02:42 by nzharkev          #+#    #+#             */
/*   Updated: 2024/11/04 08:07:47 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	g_pid = 0;

/*
 * Builds a character bit by bit based on the received signal.
 * Shifts the bits of the character left and sets the least significant bit
 * to 1 if SIGUSR1 is received, or 0 if SIGUSR2 is received.
 */

void	bin_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c = *c << 1;
}
/*
 * Stores a character in a dynamically resizing buffer.
 * Expands the buffer size if necessary, then stores the character at the
 * current index and increments the index.
 */

void	buffering(int c, int *i, int *size, char **buf)
{
	char	*new;

	new = NULL;
	if (*i >= *size)
	{
		new = ft_realloc(*buf, *size, (*size * 2));
		if (!new)
			error_msg("Malloc failed");
		*buf = new;
		*size *= 2;
	}
	(*buf)[*i] = c;
	(*i)++;
}
/*
 * Handles complete characters and stores them in a buffer.
 * If the character is the null terminator, it indicates the end of a message,
 * prints the message, resets the buffer, and sends an acknowledgment signal
 * to the client. Otherwise, it stores the character in the buffer.
 */

static void	storage(char c, int pid)
{
	static char	*buf = NULL;
	static int	size = 128;
	static int	i = 0;

	if (!buf)
	{
		buf = malloc(size);
		if (!buf)
			error_msg("Malloc failed");
	}
	if (c == '\0')
	{
		buf[i] = '\0';
		ft_printf("%s\n", buf);
		free(buf);
		buf = NULL;
		size = 128;
		i = 0;
		g_pid = 0;
		kill(pid, SIGUSR1);
	}
	else
		buffering(c, &i, &size, &buf);
}

/*
 * Signal handler that processes each incoming signal bit by bit.
 * Determines the client's PID, accumulates bits to form characters, and calls
 * storage to store the characters.
 * Sends acknowledgment to the client after each bit.
 */

static void	handler(int signum, siginfo_t *info, void *context)
{
	static int	pid = 0;
	static int	b = 7;
	static char	c;

	(void)context;
	if (g_pid == 0)
	{
		pid = info->si_pid;
		g_pid = pid;
	}
	else if (info->si_pid != pid)
		return ;
	bin_to_char(signum, &c);
	b--;
	if (b < 0)
	{
		storage(c, pid);
		c = 0;
		b = 7;
	}
	if (kill(pid, SIGUSR1) == -1)
		error_msg("Signal error");
}

/*
 * Initializes the server program, sets up the signal handler, and
 * enters an infinite loop waiting for signals. Prints the server PID on startup.
 */

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_msg("Signal error");
	while (1)
		pause();
	return (0);
}
