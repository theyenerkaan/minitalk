/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 07:45:16 by yenyilma          #+#    #+#             */
/*   Updated: 2024/11/17 08:10:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client_overall	g_client_overall;

void	context_sender(int serversig, siginfo_t *info, void *context)
{
	int	tmp;

	(void)serversig;
	(void)info;
	(void)context;
	if (g_client_overall.i >= 8)
	{
		g_client_overall.i = 0;
		g_client_overall.str++;
		if (*(g_client_overall.str) == '\0')
			exit(0);
	}
	tmp = (*(g_client_overall.str) & 1);
	*(g_client_overall.str) >>= 1;
	g_client_overall.i++;
	if (tmp == 1)
	{
		if (kill(g_client_overall.pid, SIGUSR2) == -1)
			ft_printf("%s\n", "kill error, signal cannot be sent");
	}
	else
	{
		if (kill(g_client_overall.pid, SIGUSR1) == -1)
			ft_printf("%s\n", "kill error, signal cannot be sent");
	}
}

int	main(int ac, char **av)
{
	if (ac < 3)
		ft_printf("%s\n", "there have to be at least 2 arguments");
	if (ac > 3)
		ft_printf("%s\n", "too many arguments");
	g_client_overall.pid = ft_atoi(av[1]);
	g_client_overall.str = av[2];
	g_client_overall.i = 0;
	g_client_overall.sa.sa_flags = SA_SIGINFO;
	g_client_overall.sa.sa_sigaction = context_sender;
	if (sigaction(SIGUSR1, &(g_client_overall.sa), NULL) == -1)
		ft_printf("%s\n", "sigaction error");
	context_sender(0, NULL, NULL);
	while (1)
		pause();
	return (0);
}
