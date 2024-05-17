#include<stdio.h>
#include<stdlib.h>

#define MAX 15

typedef struct memory{
    int index;
    int ini_space;
    int rem_space;
}mry;
typedef struct process{
    int id;
    int space;
}pro;
//__________________________________________________________________________
typedef struct node{
    int pro_id;
    int mry_id;
    int space;
}queue;
queue q[MAX];
int FRONT = -1;
int REAR = -1;
void enqueue(pro temp,mry tmy){
    if(FRONT == MAX){
        printf("The queue is FULL !!.\n");
        return;
    }
    else if(FRONT == -1){
        FRONT = REAR = 0;
        q[REAR].pro_id = temp.id;
        q[REAR].space = temp.space;
        q[REAR].mry_id = tmy.index;
        REAR++;
    }
    else{
        q[REAR].pro_id = temp.id;
        q[REAR].space = temp.space;
        q[REAR].mry_id = tmy.index;
        REAR++;
    }
}
queue dequeue(){
    queue ql;
    if(FRONT == -1){
        printf("The queue is EMPTY !!.\n");
    }
    else if(FRONT == REAR){
        ql = q[FRONT];
        FRONT = REAR = -1;
    }
    else{
        ql = q[FRONT++];
    }
    return ql;
}
void display(int n_m,int n_p,mry m[n_m],pro p[n_p]){
    int i,j;
    queue tempq;
    for(i = 0;i < n_m;i++){
        printf("The index of the memory segment : %d \n",m[i].index);
        printf("The initial size of memory segment : %d \n",m[i].ini_space);
        for(j = 0;j < n_p;j++){
            tempq = dequeue();
           if(tempq.mry_id == m[i].index){
                printf("P%d,",tempq.mry_id);
           }
        }
        printf("The remaining space : %d \n",m[i].rem_space);
    }
}
//________________________________________________________________________
/*void first_fit(int n_m,int n_p,mry m[n_m],pro p[n_p]){
    int i,j;
    for(i = 0;i < n_p;i++){
        for(j = 0;j < n_m;j++){
            if(m[j].rem_space > p[i].space){
                
            }
        }
    }
}*/
void initialize_process(int n_m,mry m[n_m]){
    int n_p;
    printf("Enter the number of process : ");
    scanf("%d",&n_p);

    int i;
    pro p[n_p];
    for(i = 0;i < n_p;i++){
        p[i].id = i;
        printf("Enter the size of process %d : ",p[i].id);
        scanf("%d",&p[i].space);
    }
    display(n_m,n_p,m,p);
    /*int choice;
    printf("Enter your choice : \n");
    printf("1.First Fit\n");
    printf("2.Worst Fit\n");
    printf("3.Best Fit\n");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            first_fit(n_m,n_p,m,p);
            break;
        case 2:
            worst_fit(n_m,n_p,m,p);
            break;
        case 3:
            best_fit(n_m,n_p,m,p);
            break;
    }*/
}
void initialize_memory(){
    int n;
    printf("Enter the numebr of segments of memory : ");
    scanf("%d",&n);

    int i;
    mry m[n];
    for(i = 0;i < n;i++){
        m[i].index = i;
        printf("Enter the size of the segment %d : ",m[i].index);
        scanf("%d",&m[i].ini_space);
        m[i].rem_space = m[i].ini_space;
    }
    initialize_process(n,m);
}
int main(){
    initialize_memory();
    return 0;
}
