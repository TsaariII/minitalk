/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:02:42 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/11 15:50:40 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t g_pid = 0;

void	bit_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c = *c << 1;
}

static void	sig_handler(int signum, siginfo_t *info, void *context)
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
	bit_to_char(signum, &c);
	if (b < 0)
	{
		
	}
}

int main(void)
{
	struct sigaction	sa;
	char				*pid;

	ft_memset(&sa, 0, sizeof(sa));
	ft_printf("PID: %d\n", getpid());
	free(pid);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		sleep(1);
	return (0);
}
