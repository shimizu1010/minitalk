#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

volatile sig_atomic_t g_char = 0;

void signal_handler(int signum, siginfo_t *info, void *dummy)
{
    static int i;
    char c;

    g_char = g_char << 1;
    if(signum == SIGUSR1)
        g_char |= 1;
    else if(signum == SIGUSR2)
    ;
    i++;
    c = 0xff & g_char;
    if(i == 8)
    {
        write(STDOUT_FILENO, &c, 1);
        i = 0;
    }
}

int main(void)
{
    struct sigaction act1;
    struct sigaction act2;

    printf("not so bad minitalk server pid=%d\n", getpid());
    memset(&act1, 0, sizeof(sigaction));
    memset(&act2, 0, sizeof(sigaction));
    act1.sa_sigaction = signal_handler;
    act2.sa_sigaction = signal_handler;
    act1.sa_flags = SA_SIGINFO;
    act2.sa_flags = SA_SIGINFO;
    sigaddset(&act1.sa_mask, SIGUSR2);
    sigaddset(&act2.sa_mask, SIGUSR1);
    while(1)
        pause();
}