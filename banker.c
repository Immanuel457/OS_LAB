#include <stdio.h>

#define MAX 15

int safe_sequence[MAX];

void initialize(int process,int resource,int max_matrix[MAX][MAX],int allocation_matrix[MAX][MAX],int available[MAX]){
	int i,j;
	printf("Enter the max matrix :");
	for(i = 0;i < process;i++){
		for(j = 0;j < resource;j++){
			scanf("%d",&max_matrix[i][j]);
		}	
	}
	printf("Enter the allocation matrix :");
	for(i = 0;i < process;i++){
		for(j = 0;j < resource;j++){
			scanf("%d",&allocation_matrix[i][j]);
		}	
	}
	printf("Enter the available :");
	for(j = 0;j < resource;j++){
		scanf("%d",&available[j]);
	}
}
int is_safe_state(int process, int resource, int max_matrix[MAX][MAX], int allocation_matrix[MAX][MAX], int available[MAX]) {
	int need_matrix[process][resource];
	int work[resource];
	int i,j,k = 0,count = 0,t = 1;
	for(i = 0;i < process;i++){
		for(j = 0;j < resource;j++){
			need_matrix[i][j] = max_matrix[i][j] - allocation_matrix[i][j];
		}
	}
	for(i = 0;i < resource;i++){
		work[i] = available[i];
	}
	while(t){
		for(i = 0;i < process;i++){
			int finish = 1;
			for(j = 0;j < resource;j++){
				if(need_matrix[i][j] > work[j]){
					finish = 0;
				}
			}
			if(finish == 1){
				safe_sequence[k] = i;
				k++;
				for(j = 0;j < resource;j++){
					work[j] += allocation_matrix[i][j];
				}
			}
			else if(k == i){
				t = 0;
				return 1;
			}
			else{
				count++;
				if(count > i){
					t = 0;
					return 0;
				}	
			}
		}
	}
}
int main() {
  int process,resource;
  printf("Enter the number of process : ");
  scanf("%d",&process);
  printf("Enter the number of resources : ");
  scanf("%d",&resource);
  
  int max_matrix[MAX][MAX];
  int allocation_matrix[MAX][MAX];
  int available[MAX];
  
  initialize(process,resource,max_matrix,allocation_matrix,available);
  
  if(is_safe_state(process,resource,max_matrix,allocation_matrix,available)){
  	printf("System is in a safe state.\n");
  }
  else{
  	printf("System is in an unsafe state, deadlock possible.\n");
  }

  return 0;
}

