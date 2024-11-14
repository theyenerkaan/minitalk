#include "minitalk_bonus.h"

void    handler(int signal, siginfo_t *info, void *context)
{
    static unsigned char    c;
    static int              i;

    (void)context;
    c = 0;
    if (signal == SIGUSR1)
        c |= 1 << 1;
    if(signal == SIGUSR2)
        c |= 1 << 0;
    i++;
    kill(info->si_pid, SIGUSR1);
    if (i == 8)
    {
        ft_printf("%c", c);
        i = 0;
        c = 0;
    }        
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
