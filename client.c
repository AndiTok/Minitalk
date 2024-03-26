/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atok <atok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:01:26 by atok              #+#    #+#             */
/*   Updated: 2022/12/28 16:56:10 by atok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

void	sendbits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (i & (0x01 << bit))
			kill(pid, SIGUSR1);
		else if (i | (0x01 << bit))
			kill(pid, SIGUSR2);
		bit++;
		usleep (100);
	}
}

int	main(int c, char **v)
{
	int	pid;
	int	i;

	i = 0;
	if (c == 3)
	{
		pid = ft_atoi(v[1]);
		while (v[2][i] != 0x00)
		{
			sendbits (pid, v[2][i]);
			i++;
		}
		sendbits(pid, '\n');
	}
}

/*
if (i & (0x01 << bit)) if bit 1 = bit 1
	kill(pid, SIGUSR1);
else 
OR if else (i | (0x01 << bit)) if bit 1 = bit 0 0
OR (!(i & (0x01 << bit)))
	kill(pid, SIGUSR2);
-
usleep (100); //delay the signal by 100 micro second 
				to solve the server side weird output
-
sendbits(pid, '\n'); //send a new line after finish sending message
*/