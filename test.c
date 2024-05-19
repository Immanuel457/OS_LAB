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
        printf("%d,",s[i].id);
    }
    printf("\n");
}
void recent_indicator(int n_pf,stack s[n_pf],int j){
    int i = n_pf; 
    s[j].index = n_pf;
    while(0 < i){
        if(s[i].id == -1){
            i--;
        }
        else{
            if(i == j){
                i--;
            }
            else{
                s[i].index--;
                i--;
            }
        }
    }
}
void LRU(int n_p,int n_pf,int p[n_p],stack s[n_pf]){
    int i,j = 0,k = 0,hit = 0,check;
    for(i = 0;i < n_p;i++){
        //printf("j = %d\n",j);
        while(j < n_pf){
            if(s[j].id == -1){
                s[j].id = p[i];
                recent_indicator(n_pf,s,j);
                j++;
                break;
            }
            else{
                check = check_similar(p[i],n_pf,s);
                //printf("check = %d",check);
                if(check != 1){
                    k = 0;
                    while(k < n_pf){
                        if(s[k].index == 1){
                            j = k;
                            //break;
                        }
                        k++;
                    }
                    //printf("j = %d\n",j);
                    s[j].id = p[i];
                    recent_indicator(n_pf,s,j);
                    j++;
                    break;
                }
                else{
                    recent_indicator(n_pf,s,j);
                    hit++;
                    j++;
                    break;
                }
                //printf("j = %d\n",j); 
            }
        }
        if(j == n_pf){
            j = 0;
        }
        //printf("i = %d\n",i);
        //printf("j = %d\n",j);
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
    LRU(n_p,n_pf,p,s);
}
void initialize_process(){
    int n = 8;
    /*printf("Enter the number of process in the sequence : ");
    scanf("%d",&n);*/

    int i;
    int p[] = {1,2,5,3,2,3,1,5};
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
