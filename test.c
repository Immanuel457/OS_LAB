#include<stdio.h>
#include<stdlib.h>
#define max 20

typedef struct page_frame{
    int id;
    int index;
}frame;
int n_p;
int n_pf = 2;
int p[] = {1,2,3,4,3,1,2,4,5,2,1,2,3,4};
frame f[2];

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
    int j,k = 0,index = 0;
    for(j = i+1;j < n_p;j++){
        while(k < n_pf){
            if(f[k].id == p[j]){
                f[k].index = index;
                index++;
            }
            k++;
        }
    }
}
void Optimal(){
    int i,j = 0,hit,check;
    for(i = 0;i < n_p;i++){
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
                printf("check = %d",check);
                if(check != 1){
                    int k = 0;
                    int min = 99;
                    while(k < n_pf){
                        if(min > f[k].index){
                            min = f[k].index;
                            j = k;
                        }
                        printf("i = %d,j = %d,\n",i,j);
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
        //display();
        //printf("\n");
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
    n_p = 14;
    //printf("Enter the process id  : \n");
    /*for(int i = 0;i < n;i++){
        scanf("%d",&p[i]);
    }*/
    initialize_frame();
}
int main(){
    initialize();
    Optimal();
    return 0;
}