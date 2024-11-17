#include "minitalk_bonus.h"

void    handler(int signal, siginfo_t *info, void *context)
{
    static t_server_overall server_overall;

    (void)context;
    if (info->si_pid != 0)
        server_overall.pid = info->si_pid;
    if (signal == SIGUSR2)
        server_overall.c |= 1 << 7;
    if(server_overall.i < 7)
        server_overall.c >>= 1;
    server_overall.i++;
    if (server_overall.i > 7)
    {
        ft_printf("%c", server_overall.c);
        server_overall.i = 0;
        server_overall.c = 0;
    }
    if (kill(info->si_pid, SIGUSR1) == -1)
        ft_printf("%s\n", "kill error, signal cannot be sent");
}

int main(int ac, char **av)
{
    struct sigaction	sig;
    if (ac != 1)
        ft_printf("%s\n", "too many arguments");
    (void)av;
    ft_printf("pid: %d\n", getpid());
    sig.sa_sigaction = handler;
    sig.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &sig, NULL) == -1)
        ft_printf("%s\n", "sigaction error");
    if (sigaction(SIGUSR2, &sig, NULL) == -1)
        ft_printf("%s\n", "sigaction error");
    while (1)
        pause();
}
