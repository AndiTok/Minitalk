/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:01:29 by atok              #+#    #+#             */
/*   Updated: 2023/01/11 22:47:54 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	handler(int signal, siginfo_t *info, void *s)
{
	static int	bit;
	static char	c;

	(void) info;
	(void) s;
	if (signal == SIGUSR1)
		c = c + (0x01 << bit);
	else if (signal == SIGUSR2)
		c = c + (0x00 << bit);
	bit++;
	if (bit == 8 && c == '\n')
		kill(info->si_pid, SIGUSR2);
	if (bit == 8)
	{
		write (1, &c, 1);
		bit = 0;
		c = 0;
	}
}

void	writepid(unsigned int pid)
{
	if (pid >= 10)
	{
		writepid(pid / 10);
	}
	write (1, &"0123456789"[pid % 10], 1);
}

int	main(int c, char **v)
{
	int					pid;
	struct sigaction	cmd;

	cmd.sa_sigaction = handler;
	cmd.sa_flags = SA_SIGINFO;
	pid = 0;
	(void)v;
	if (c == 1)
	pid = getpid();
	write(1, "PID : ", 7);
	writepid(pid);
	write (1, "\n", 1);
	while (c == 1)
	{
		sigaction(SIGUSR1, &cmd, NULL);
		sigaction(SIGUSR2, &cmd, NULL);
	}
}

//gcc server.c -o server && ./server 1

/* write pid can also use
static void	writepid(pid_t pid) //pid_int aka int
{
	char output

	if (pid <9)
	{
		writepid (pid/10)
	}
	c = pid % 10 + '0'
	write (1, &output, 1);
}
*/

/* If SA_SIGINFO is specified in sa_flags, 
then sa_sigaction (instead of sa_handler) 
specifies the signal-handling function for signum. 
This function receives the signal number as its 
first argument, a pointer to a siginfo_t as its 
second argument and a pointer to 
a ucontext_t (cast to void *) as its third argument. */