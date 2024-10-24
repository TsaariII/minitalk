/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:02:42 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/24 13:55:35 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t g_pid = 0;

void	bin_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c = *c << 1;
}

static void	storage(char c, int pid)
{
	 static char	*buf = NULL;
	 static int		size = 128;

	 if (!buf)
	 {
		buf = malloc(size);
		if (!buf)
			error("Malloc failed");
	 }
	 if (c == '\0')
	 {
		ft_printf("\n");
		free(buf);
		buf = NULL;
		size = 128;
		kill(pid, SIGUSR1);
	 }
	 else
	 	ft_realloc(buf, size, size);
}

static void	handler(int signum, siginfo_t *info, void *context)
{
	static int	pid;
	static int	b;
	static char	c;

	b = 7;
	(void)context;
	if (g_pid == 0)
	{
		pid = info->si_pid;
		g_pid = pid;
	}
	else if (info->si_pid != pid)
		return ;
	bin_to_char(signum, &c);
	if (b < 0)
	{
		storage(c, pid);
		c = 0;
		b = 7;
	}
	if (kill(pid, SIGUSR1) == -1)
		error("Signal error");
}

int main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error("Signal error");
	while (1)
		pause();
	return (0);
}
