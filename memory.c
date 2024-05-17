#include<stdio.h>
#include<stdlib.h>

typedef struct process{
	int id;
	int space;
	struct process *next;
}pro;
pro *pr = NULL;
typedef struct memory{
	int ini_space;
	int rem_space;
	int id;
	struct list{
		int id;
		struct list *next;
	};
}mry;
void display(int n,mry m[n]){
	int i;
	for(i = 0;i < n;i++){
		printf("Allocation of memory segment %d :\n",m[i].id);
		printf("Initial size : %d\n",m[i].ini_space);
		printf("Allocation sequence is : ");
		pro *current = m[i].list;
		while(current != NULL){
			printf("P%d  ",current->id);
			current = current->next;
		}
		printf("\n");
		printf("Remaining size : %d\n",m[i].rem_space);
	}
}
//-----------------------------------------------------------------------
void initialize_memory(){
	int n;
	mry m[n];
	printf("Enter the number of memory segments : "); 
	scanf("%d",&n);
	int i;
	for(i = 0;i < n;i++){
		m[i].id = i;
		printf("Enter the size of memory in segment %d : ",m[i].id);
		scanf("%d",&m[i].ini_space);
		m[i].rem_space = m[i].ini_space;
		m[i].list = NULL;
	}
	display(n,m);
	
	for(i = 0;i < n;i++){
		pro *current = m[i].list;
		while(current != NULL){
			pro *temp = current;
			current = current-> next;
			free(temp);
		}
	}
}
int main(){
	initialize_memory();
	//memory_allocation();
	return 0;
}
