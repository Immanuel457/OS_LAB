#include<stdio.h>
#include<stdlib.h>

typedef struct process{
    int pid;
    int pat;
    int pbt;
    int pct;
    int tat;
    int pwt;
    int prt;
}pro;

int gannt[15][2];

void bubblesort(int n,pro p[n]){
    int i,j;
    pro temp;
    for(i = 0;i < n;i++){
        for(j = i;j < n;j++){
            if(p[j].pat < p[i].pat){
                temp = p[j];
                p[j] = p[i];
                p[i] = temp; 
            }
        }
    }
}
void rearrange(int max,int i,int j,pro p[max]){
    int m,n;
    pro temp;
    for(m = i;m < j;m++){
        for(n = m;n < j;n++){
            if(p[n].pbt < p[m].pbt){
                temp = p[n];
                p[n] = p[m];
                p[m] = temp;
            }
        }
    }
}
void display(int n,pro p[n]){
    int i;
    printf("pid\t at\t bt\t ct\ttat\t wt\t rt\n");
    for(i = 0;i < n;i++){
        printf("%d \t%d \t%d \t%d \t%d \t%d \t%d \n",p[i].pid,p[i].pat,p[i].pbt,p[i].pct,p[i].tat,p[i].pwt,p[i].prt);
    }
}

void fcfs(int n){
    pro p[n];
    int i,j;
    double avgtat=0,avgwt=0;
    for(i = 0;i < n;i++){
        p[i].pid = i;
        printf("Enter the arrival time of process %d : ",i);
        scanf("%d",&p[i].pat);
        printf("Enter the burst time of process %d : ",i);
        scanf("%d",&p[i].pbt);
    }
    bubblesort(n,p);
    i = 0;
    int ct = p[i].pat;

    do{
        gannt[i][0] = p[i].pid;
        gannt[i][1] = ct;
        p[i].pct = ct + p[i].pbt;
        p[i].tat = p[i].pct - p[i].pat;
        p[i].pwt = p[i].tat - p[i].pbt;
        p[i].prt = gannt[i][1] - p[i].pat;
        ct = p[i].pct;
        i++;
    }while(i < n);
    display(n,p);
    for(i = 0;i < n;i++){
        avgtat = avgtat + p[i].tat;

        avgwt = avgwt + p[i].pwt;
    }
    double throughput = 0;
    throughput = p[n-1].pct;
    printf("Average Turn Around Time : %f\n",avgtat/n);
    printf("Average Waiting Time : %f\n",avgwt/n);
    printf("The throughput is : %f\n",n/throughput);
}
void sjf(int n){
    pro p[n];
    int i,j;
    double avgtat,avgwt;
    for(i = 0;i < n;i++){
        p[i].pid = i;
        printf("Enter the arrival time of process %d : ",i);
        scanf("%d",&p[i].pat);
        printf("Enter the burst time of process %d : ",i);
        scanf("%d",&p[i].pbt);
    }
    bubblesort(n,p);
    i = 0,j = 0;
    int ct = p[i].pat;
    do{
        if(j != n && i != 0 && p[i].pat < p[i].pct){
            
            j = i+1;
            while(p[j].pat < p[i].pct && j < n){
                
                j++;
            }
            rearrange(n,i,j,p);    
        }
        
        gannt[i][0] = p[i].pid;
        gannt[i][1] = ct;
        p[i].pct = ct + p[i].pbt;
        p[i].tat = p[i].pct - p[i].pat;
        p[i].pwt = p[i].tat - p[i].pbt;
        p[i].prt = gannt[i][1] - p[i].pat;
        ct = p[i].pct;
        i++;
    }while(i < n);
    bubblesort(n,p);
    display(n,p);
    for(i = 0;i < n;i++){
        avgtat = avgtat + p[i].tat;
        avgwt = avgwt + p[i].pwt;
    }
    double throughput = p[n].pct/n;
    printf("Average Turn Around Time : %lf\n",avgtat/n);
    printf("Average Waiting Time : %lf\n",avgwt/n);
    printf("The throughput is : %lf\n",n/throughput);
}

int main(){
    int n,choice;
    while(1){
        printf("Enter your choice : ");
        printf("\n1.FCFS\n2.SJF\n3.Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter the number of process : ");
                scanf("%d",&n);
                fcfs(n);
                break;
            case 2:
                printf("Enter the number of process : ");
                scanf("%d",&n);
                sjf(n);
                break;
            case 3:
                return 0;
        }
    }
}
