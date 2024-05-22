#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

int main(){
    pid_t p0 = fork();
    printf("Currently in process p0 pid = %d\n",getpid());
    printf("Creating child process p1.\n");
    pid_t p1 = fork();
    if(p1 == 0){
        printf("Currently in process p1 pid = %d\n",getpid());
        printf("Creating child process p2.\n");
        pid_t p2 = fork();
        if(p2 == 0){
            printf("Currently in process p2 pid = %d\n",getpid());
            printf("Creating child process p4.\n");
        }
        else{
            p2 = wait(NULL);
            kill(p2,SIGTERM);
            printf("process p2 terminated !!.");
        }
        printf("Creating child process p3.\n");
        pid_t p3 = fork();
        if()
    }
    else{
        p1 = wait(NULL);
        kill(p1,SIGTERM);
        printf("process p1 terminated !!.");
    }
    return 0;
}
