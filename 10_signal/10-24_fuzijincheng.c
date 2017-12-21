#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static void user1(int signo)
{
    printf("parent accept child signal \n");
}
static void user2(int signo)
{
    printf("child accept parent signal \n");
}

int sum = 0;
int numc =0 ;
int nump = 0;
int main(void)
{
    printf("program start:\n");
    pid_t child;
    child = fork();
    if(child <0 )
    {
        printf("fork error\n");
        return -1;
    }
    else if(child == 0)
    {
        sigset_t newmask,waitmask,oldmask;
        
        printf("child start:\n");
        signal(SIGUSR2,user2);
        sigemptyset(&newmask);
        sigemptyset(&waitmask);
        sigaddset(&newmask, SIGUSR2);

        sigprocmask(SIG_BLOCK,&newmask,&oldmask);
        // for(int i=0; i<3; i++)
        // {
        //     printf("child %d\n",i);
        //     sleep(1);
        // }
        numc = 4;
        kill(getppid(),SIGUSR1);
        sigsuspend(&waitmask);
        sum = numc + nump;
        printf("child calculate sum is :%d\n", sum);
        sigprocmask(SIG_BLOCK,&oldmask,NULL);
        printf("child end\n");
        exit(0);
    }
    else
    {
        sigset_t newmask,oldmask,waitmask;
        printf("parent start:\n");
        signal(SIGUSR1, user1);
        printf("child id is %ld\n",child);
        sigemptyset(&newmask);
        sigemptyset(&waitmask);
        sigaddset(&newmask, SIGUSR1);
        sigprocmask(SIG_BLOCK,&newmask,&oldmask);
        // for(int i=0; i<3; i++)
        // {
        //     printf("parent %d\n",i);
        //     sleep(1);
        // }
        nump =3;
        // sleep(3);
        kill(child, SIGUSR2);
        printf("parent send signal to child1\n");
        // printf("parent send signal to child2\n");
        sigsuspend(&waitmask);
        sum = numc+nump;
        printf("parent calculate sum is :%d\n", sum);
        sigprocmask(SIG_BLOCK,&oldmask,NULL);
        printf("parent end\n");
        exit(0);
    }
}