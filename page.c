#include<stdio.h>
#include<stdlib.h>

//___________________________________________________________________________
typedef struct paging_stack{
    int id;
    int count;
    int index;
}stack;
int FRONT = -1;
//____________________________________________________________________________
int check_similar(int temp,int n_pf,stack s[n_pf]){
    int flag = 0;
    for(int i = 0;i < n_pf;i++){
        if(temp == s[i].id){
            flag = 1;
        }
    }
    return flag;
}
void display(int n_pf,stack s[n_pf]){
    int i;
    for(i = 0;i < n_pf;i++){
        printf("%d,",s[i.id]);
    }
}
void FCFS(int n_p,int n_pf,int p[n_p],stack s[n_pf]){
    int i,j,hit,check;
    for(i = 0;i < n_p;i++){
        while(j < n_pf){
            if(s[j] == -1){
                s[j] = p[i];
                break;
            }
            else{
                check = check_similar(p[i],n_pf,s);
                if(check != 1){
                    check = hit;
                    s[j] = p[i];
                    j++;
                    break;
                }
                else{
                    hit++;
                    j++;
                    break;
                }
            }
        }
        if(j == n_p) j = 0;

        display(n_pf,s);
    }
}
void initialize_page_frame(int n_p,int p[n_p]){
    int n_pf;
    printf("Enter the number of frames in a single page : ");
    scanf("%d",&n_pf);

    // initializing the page frame 
    stack s[n_pf];
    for(int i = 0;i < n_pf;i++){
        s[i].id = -1;
        s[i].count = 0;
        s[i].index = -1;
    }
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
    int n;
    printf("Enter the number of process in the sequence : ");
    scanf("%d",&n);

    int i,j;
    int p[n];
    printf("Enter the order of process : \n");
    for(i = 0;i < n;i++){
        scanf("%d",&p[i]);
    }
    initialize_page_frame(n,p);
}
int main(){
    initialize_process();
    return 0;
}
