/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:01:29 by atok              #+#    #+#             */
/*   Updated: 2022/12/31 01:00:22 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	handler(int signal)
{
	static int	bit;
	static char	c;

	if (signal == SIGUSR1)
		c = c + (0x01 << bit);
	else if (signal == SIGUSR2)
		c = c + (0x00 << bit);
	bit++;
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
	int	pid;

	pid = 0;
	(void)v;
	if (c == 1)
	pid = getpid();
	write(1, "PID : ", 7);
	writepid(pid);
	write (1, "\n", 1);
	while (c == 1)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
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
/* 
	while (c == 1)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		pause(); // optional
	}
 */