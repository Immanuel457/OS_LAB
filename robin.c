#include<stdio.h>
#include<stdlib.h>

#define MAX 20

typedef struct process{
	int id;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int rt;
	int remaint;
}pro;
typedef struct chart{
	int id;
	int time;
}gannt;
gannt g[MAX];
void bubblesort(int n,pro p[n]){
	pro temp;
	for(int i = 0;i < n;i++){
		for(int j = i;j < n;j++){
			if(p[j].at < p[i].at){
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;				
			}
		}
	}
}
void sort(int n,pro p[n]){
	pro temp;
	for(int i = 0;i < n;i++){
		for(int j = i;j < n;j++){
			if(p[j].id < p[i].id){
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
}
void gsort(int n){
  gannt temp;
  for(int i = 0;i < n;i++){
    for(int j = i;j < n;j++){
      if(g[j].id < g[i].id){
        temp = g[j];
        g[j] = g[i];
        g[i] = temp;
      }
    }
  }
}
void display(int n,pro p[n]){
	printf("id \tat \tbt \tct \ttat\twt \trt \n");
	for(int i = 0;i < n;i++){
		printf("%d \t%d \t%d \t%d \t%d \t%d \t%d \t%d \n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt,g[i].time);
	}
}

void rnd_rbn(int n,int quant,pro p[n]){
	int pos = 0,count = 0,i = 0;
	int time = p[pos].at;
	bubblesort(n,p);
	do{
	        if(g[pos].id != p[pos].id){
	                g[pos].id = p[pos].id;
	                g[pos].time = time;
	        }
		if(p[pos].remaint == 0){
			count++;
		}
		else if(p[pos].remaint < quant){
			time = time + p[pos].remaint;
			p[pos].ct = time;
			p[pos].remaint = 0;
		}
		else{
			time = time + quant;
			p[pos].ct = time;
			p[pos].remaint = p[pos].remaint - quant;
		}
		pos = (pos + 1)%n;
	}while(count < n*n);
	gsort(n);
	sort(n,p);
	//Calculate tat wt rt
	for(i = 0;i < n;i++){
	  p[i].tat = p[i].ct - p[i].at;
	  p[i].wt = p[i].tat - p[i].bt;
	  p[i].rt = g[i].time - p[i].at;
	}
	display(n,p);
	// Average Calculation
	double avgtat,avgwt,avgrt,throughput;
	for(i = 0;i < n;i++){
	  avgtat += p[i].tat;
	  avgwt += p[i].wt;
	  avgrt += p[i].rt;
	}
	printf("The average turn around time :  %f\n",avgtat/n);
	printf("The average waiting time : %f\n",avgwt/n);
	printf("The average response time : %f\n",avgrt/n);
	printf("The throughput is : %f\n",n/p[n-1].ct);
}
void initialize(int n,int q){
	int i,j;
	pro p[n];
	int id[] = {1,2,3,4,5};
	int at[] = {0,5,12,2,9};
	int bt[] = {11,28,2,10,16};
	for(i = 0;i < n;i++){
		p[i].id = id[i];
		p[i].at = at[i];
		p[i].bt = bt[i];
		p[i].remaint = bt[i];
	}
	rnd_rbn(n,q,p);
}

int main(){
	int n = 5;
	int quant = 5;
	initialize(n,quant);
	return 0;
}
