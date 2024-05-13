#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void send_char(const pid_t pid, char c){
    int digit;
    digit = 7;

    while(digit >= 0)
    {
        if(c & (1 << digit))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        digit--;
        usleep(100);
    }
}

void send_str(const pid_t pid, char *str){
    while(*str)
    {
        send_char(pid, *str);
        str++;
    }
}

int main(int argc, char **argv)
{
    int pid;
    if(argc != 3)
        return (1);
    pid = atoi(argv[1]);
    send_str(pid, argv[2]);
}