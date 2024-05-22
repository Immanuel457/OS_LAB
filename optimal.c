##include<stdio.h>
#include<stdlib.h>
#define max 20

typedef struct page_frame{
    int id;
    int index;
}frame;
int n_p = 14;
int n_pf = 4;
int p[] = {1,2,3,4,3,1,2,4,5,2,1,2,3,4};
frame f[4];

void display(){
    for(int i = 0;i < n_pf;i++){
        printf("%d,",f[i]);
    }
}
int check_similar(int i){
    for(int j = 0;j < n_pf;j++){
        if(p[i] == f[j].id){
            return 1;
        }
    }
    return 0;
}
void future_index(int i){
    int k,index = 0;
    int v = n_p;
    for(int n = 0;n < n_pf;n++){
        f[n].index = 0;
    }
    for(;v > i;v--){
        k = 0;
        while(k < n_pf){
            if(f[k].id == p[v]){
                f[k].index = v;
            }
            k++;
        }
    }
}
void Optimal(){
    int i,j = 0,hit,check = 0;
    for(i = 0;i < n_p;i++){
        //printf("{p[i] = %d}",p[i]);
        while(j < n_pf){
            if(f[j].id == -1){
                future_index(i);
                check = check_similar(i);
                if(check != 1){
                    f[j].id = p[i];
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
                future_index(i);
                check = check_similar(i);
                //printf("check = %d",check);
                if(check != 1){
                    int k = 0;
                    int mx = 0;
                    while(k < n_pf){
                        if(mx < f[k].index){
                            mx = f[k].index;
                            j = k;
                        }
                        k++;
                    }
                    f[j].id = p[i];
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
        if(j == n_pf) j = 0;
        display();
        printf("\n");
    }
}
void initialize_frame(){
    for(int i = 0;i < n_pf;i++){
        f[i].id = -1;
        f[i].index = 0;
    }
}
void initialize(){
    //printf("Enter the number of process : ");
    //scanf("%d",&n_p);
    //n_p = 14;
    //printf("Enter the process id  : \n");
    /*for(int i = 0;i < n;i++){
        scanf("%d",&p[i]);
    }*/
    //initialize_frame();
}
int main(){
    //initialize();
    initialize_frame();
    Optimal();
    return 0;
}
