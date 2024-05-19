#include<stdio.h>
#include<stdlib.h>
#define MAX 1100

//___________________________________________________________________________
typedef struct paging_stack{
    int id;
    int count;
    int index;
}stack;
int FRONT = -1;
//____________________________________________________________________________
int OPT_check_similar(int temp,int n_pf,stack s[n_pf]){
    int flag = 0;
    for(int i = 0;i < n_pf;i++){
        if(temp == s[i].id){
            s[i].count--;
            flag = 1;
        }
    }
    return flag;
}
void display(int n_pf,stack s[n_pf]){
    int i;
    for(i = 0;i < n_pf;i++){
        printf("%d,",s[i].id);
    }
    printf("\n");
}
void future_count(int n_p,int n_pf,int p[n_p],stack s[n_pf],int t){
    int i,j;
    for(i = 0;i < n_pf;i++){
        s[i].count = 0;
    }
    for(i = t;i < n_p;i++){
        for(j = 0;j < n_pf;j++){
            if(p[i] == s[j].id){
                s[j].count++;
            }
        }
    }
}
void OPTIMAL(int n_p,int n_pf,int p[n_p],stack s[n_pf]){
    int i,j = 0,hit = 0,check;
    for(i = 0;i < n_p;i++){
        while(j < n_pf){
            if(s[j].id == -1){
                future_count(n_p,n_pf,p,s,i);
                check = OPT_check_similar(p[i],n_pf,s);
                if(check != 1){
                    s[j].id = p[i];
                    s[j].count--;
                    j++;
                    break;
                }
                else{
                    hit++;
                    j++;
                    break;
                }
            }
            else{
                future_count(n_p,n_pf,p,s,i);
                check = OPT_check_similar(p[i],n_pf,s);
                if(check != 1){
                    int k = 0;
                    int min = MAX;
                    while(k < n_pf){
                        if(s[k].count < min){
                            min = s[k].count;
                            j = k;
                        }
                        //printf("i = %d count = %d\n",s[k].id,s[k].count);
                        k++;
                    }
                    s[j].id = p[i];
                    s[j].count--;
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
        if(j == n_pf){
            j = 0;
        }
        display(n_pf,s);
    }
}
//-------------------------------------------------------------------------------
void initialize_page_frame(int n_p,int p[n_p]){
    int n_pf = 2;
    /*printf("Enter the number of frames in a single page : ");
    scanf("%d",&n_pf);*/

    // initializing the page frame 
    stack s[n_pf];
    for(int i = 0;i < n_pf;i++){
        s[i].id = -1;
        s[i].count = 0;
        s[i].index = -1;
    }
    OPTIMAL(n_p,n_pf,p,s);
}
void initialize_process(){
    int n = 8;
    /*printf("Enter the number of process in the sequence : ");
    scanf("%d",&n);*/

    int i;
    int p[] = {1,2,5,1,3,2,1,3};
    printf("Enter the order of process : \n");
    /*for(i = 0;i < n;i++){
        scanf("%d",&p[i]);
    }*/
    initialize_page_frame(n,p);
}
int main(){
    initialize_process();
    return 0;
}
