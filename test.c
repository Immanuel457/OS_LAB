#include<stdio.h>
#include<sys/types.h>
#include<sys/unistd.h>
#include<semaphores.h>
#include<wait.h>
#include<signal.h>

int main(){
    pid_t p0 = fork();
    printf("Currently in process p0 pid = %d\n",getpid());
    printf("Creating child process p1.\n");
    pid_t p1 = fork();
    if(p1 == -1){
        perror("fork p1 failed.\n");
        exit(1);
    }
    else if(p1 == 0){
        printf("Currently in process p1 pid = %d\n",getpid());
        printf("Creating child process p2.\n");
        pid_t p2 = fork();
        if(p2 == -1){
            perror("fork p2 failed.\n");
            exit(1);
        }
        else if(p2 == 0){
            printf("Currently in process p2 pid = %d\n",getpid());
            printf("Creating child process p4.\n");
            pid_t p4 = fork();
            if(p4 == -1){
                perror("fork p4 failed.\n");
                exit(1);
            }
            else if(p4 == 0){
                printf("Currently in process p4 pid = %d\n",getpid());
                sleep(3);
            }
            else{
                p4 = wait(NULL);
                kill(p4,SIGTERM);
                printf("process p4 terminated !!.\n");
            }
            printf("Creating child process p5.\n");
            pid_t p5 = fork();
            if(p5 == -1){
                perror("fork p5 failed.\n");
                exit(1);
            }
            else if(p5 == 0){
                printf("Currently in process p5 pid = %d\n",getpid());
                sleep(3);
            }
            else{
                p5 = wait(NULL);
                kill(p5,SIGTERM);
                printf("process p5 terminated !!.\n");
            }
        }
        else{
            p2 = wait(NULL);
            kill(p2,SIGTERM);
            printf("process p2 terminated !!.\n");
        }
        printf("Creating child process p3.\n");
        pid_t p3 = fork();
        if(p3 == -1){
            perror("fork p3 failed.\n");
            exit(1);
        }
        else if(p3 == 0){
            printf("Currently in process p3 pid = %d\n",getpid());
            printf("Creating child process p6.\n");
            pid_t p6 = fork();
            if(p6 == -1){
                perror("fork p6 failed.\n");
                exit(1);
            }
            else if(p6 == 0){
                printf("Currently in process p6 pid = %d\n",getpid);
                sleep(3);
            }
            else{
                p6 = wait(NULL);
                kill("p6",SIGTERM);
                printf("process p6 terminated !!.\n");
            }
            printf("Creating child process p7.\n");
            pid_t p7 = fork();
            if(p7 == -1){
                perror("fork p7 failed.\n");
                exit(1);
            }
            else if(p7 == 0){
                printf("Currently in process p7 pid = %d\n",getpid);
                sleep(3);
            }
            else{
                p7 = wait(NULL);
                kill("p7",SIGTERM);
                printf("procewss p7 terminated !!.\n");
            }
        }
        else{
            p3 = wait(NULL);
            kill(p3,SIGTERM);
            printf("process p3 terminated !! .\n");
        }
    }
    else{
        p1 = wait(NULL);
        kill(p1,SIGTERM);
        printf("process p1 terminated !!.");
    }
    return 0;
}
