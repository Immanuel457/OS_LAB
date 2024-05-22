#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/unistd.h>
#include<sys/wait.h>

void prime(int n){
    int i,j,flag = 0;
    printf("prime numbers are - ");
    for(i = 2;i < n;i++){
        flag = 0;
        for(j = 2;j < i/2;j++){
            if(i%j == 0){
                flag++;
            }
        }
        if(flag < 2){
            printf("%d,",i);
        }
    }
    printf("\n");
}
int main(){
    pid_t p0 = fork();
    if(p0 == -1){
        perror("Failed to create child !! \n");
        exit(1);
    }
    else if(p0 == 0){
        pid_t p1 = fork();
        if(p1 == -1){
            perror("Failed.\n");
            exit(1);
        }
        else if(p1 == 0){
            int n;
            printf("Enter the limit : ");
            scanf("%d",&n);
            
            pid_t p3 = fork();
            if(p3 == -1){
                perror("Failed \n");
                exit(1);
            }
            else if(p3 == 0){
                prime(n);
                exit(0);
            }
            else{
                p3 = wait(NULL);
                printf("Completed p3\n");
                exit(0);
            }
            exit(0);
        }
        else{
            p1 = wait(NULL);
            printf("Completed p1\n");
            exit(0);
        }
        exit(0);
    }
    else{
        p0 = wait(NULL);
        printf("Completed !!\n");
        exit(0);
    }
    return 0;
}
