#include<stdio.h>
#include<stdlib.h>

//___________________________________________________________________________
typedef struct paging_stack{
    int id;
}stack;
int FRONT = -1;
void push(){

}
//____________________________________________________________________________
void initialize_page_frame(int n_p,int p[n_p]){
    int n_pf;
    printf("Enter the number of frames in a single page : ");
    scanf("%d",&n_pf);

    // initializing the page frame 
    stack s[n_pf];

    int choice;
    printf("Enter your choice : \n");
    printf("1.FCFS");
    printf("2.LRU");
    printf("3.LFU");
    printf("4.Optimal");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            FCFS(n_p,n_pf,p,s);
            break;
    }
}
void initialize_process(){
    int n
    printf("Enter the number of process in the sequence : ");
    scanf("%d",&n);

    int i,j;
    int p[n];
    printf("Enter the order of process : \n");
    for(i = 0;i < n;i++){
        scanf("%d",&p[i]);
    }
}
int main(){
    initialize_process();
    return 0;
}