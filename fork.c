#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
  pid_t p0 = fork();
  if(p0 == 0){
    pid_t gp0 = getpid();
    pid_t p1 = fork(); 
    printf("%d\n",gp0);
    if(p1 == 0){
      pid_t gp1 = getpid();
      pid_t p3 = fork();
      printf("%d\n",gp1);
      if(p3 == 0){
        pid_t gp3 = getpid();
        pid_t p5 = fork();
        printf("%d\n",gp3);
        if(p5 == 0){
          pid_t gp5 = getpid();
          printf("%d\n",gp5);
          printf("1");
        }
      }
    }
    else{
      pid_t p2 = fork();
      if(p2 == 0){
        pid_t gp2 = getpid();
        pid_t p4 = fork();
        printf("%d\n",gp2);
        if(p4 == 0){
          pid_t gp4 = getpid();
          printf("%d\n",gp4);
        }
      }
    }
  }
  else{
    printf("w");
  }
  return 0;
}
