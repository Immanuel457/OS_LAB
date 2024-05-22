#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/unistd.h>
#include<sys/wait.h>

int main(){
    int n[2];
    if(pipe(n) == -1){
        perror("pipe creation failed.\n");
        exit(1);
    }
    pid_t p0 = fork();
    if(p0 == -1){
        perror("Child creation failed.\n");
        exit(1);
    }
    else if(p0 == 0){
        int i,temp;
        close(n[0]);
        for(i = 0;i < 10;i++){
            printf("Enter the value : ");
            scanf("%d",&temp);
            if(write(n[1],&temp,sizeof(int)) == -1){
                perror("write failed");
                exit(1);
            }
        }
        close(n[1]);
        exit(0);
    }
    else{
        p0 = wait(NULL);
        int i,temp;
        close(n[1]);
        for(i = 0;i < 10;i++){
            if(read(n[0],&temp,sizeof(int)) == -1){
                perror("read failed");
                exit(1);
            }
            printf("The value is : %d\n",temp);
        }
        close(n[0]);
        exit(0);
    }
    return 0;
}
