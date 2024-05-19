#include<stdio.h>
#include<stdlib.h>
#include<wait.h>

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
	int i,j;
	pro temp;
	for(i = 0;i < n;i++){
		for(j = i;j < n;j++){
			if(p[j].at < p[i].at){
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
}
int arrange(int n,int time,pro p[n]){
	int i,j,pos = 0,max = 0;
	pro temp;
	int count = 0;
	while(p[pos].remaint == 0 && pos < n){
		pos++;
	}
	if(pos == n){
		return pos;
	}
	while(p[max].at <= time && max < n){
		max++;
	}
	for(i = pos;i < max;i++){
		for(j = i;j < max;j++){
			if(p[j].remaint < p[i].remaint){
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
	return pos;
}
void sort(int n,pro p[n]){
	pro temp;
	gannt gtemp;
	for(int i = 0;i < n;i++){
		for(int j = i;j < n;j++){
			if(p[j].id < p[i].id){
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
			if(g[j].id < g[i].id){
				gtemp = g[j];
				g[j] = g[i];
				g[i] = gtemp; 
			}
		}
	}
}
int calgannt(int n,int j,int time,int pos,pro p[n]){
	int i,flag = 0;
	for(i = 0;i < n;i++){
		if(g[i].id == p[pos].id){
			flag = 1;
			break;
		}
		else{
			flag = 0;
		}
	}
	if(flag == 0){
		g[j].id = p[pos].id;
		g[j].time = time;
		j++;
	}
	return j;
}
void display(int n,pro p[n]){
	int i;
	printf("id \tat \tbt \tct \ttat\twt \trt \tGannt chart\n");
	for(i = 0;i < n;i++){
		printf("%d \t%d \t%d \t%d \t%d \t%d \t%d \t%d \n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt,g[i].time);
	}
}
void srtf(int n,pro p[n]){
	int i = 0,j = 0,pos = 0,count = 0;
	pro temp;
	int time = p[pos].at;
	bubblesort(n,p);
	do{
      		//j = calgannt(n,j,time,pos,p);
      		pos = arrange(n,time,p);
      		j = calgannt(n,j,time,pos,p);
      		p[pos].ct = time + 1;
      		time = p[pos].ct;
      		p[pos].remaint--;
      		if(p[pos].remaint == 0){
      			count ++;
      		}
      		//printf("%d\n",ct);
	}while(count < n);
	sort(n,p);
	// Calculation of TAT WT RT
	for(i = 0;i < n;i++){
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;
		p[i].rt = g[i].time - p[i].at;
	}
	display(n,p);
	//Average calculation
	double avgtat,avgwt,avgrt,throughput;
	for(i = 0;i < n;i++){
		avgtat += p[i].tat;
		avgwt += p[i].wt;
		avgrt += p[i].rt;
	}
	printf("The average of turn around time is : %f\n",avgtat/n);
	printf("The average of waiting times is : %f\n",avgwt/n);
	printf("The average of response times is : %f\n",avgrt/n);
	throughput = n/time;
	printf("The Throughput is : %f\n",n/time);
}

void initialize(int n){
	int i;
	pro p[n];
	for(i = 0;i < n;i++){
		p[i].ct = 0;
	}
	int id[] = {1,2,3,4,5};
	int at[] = {0,5,12,2,9};
	int bt[] = {11,28,2,10,16};
	for(i = 0;i < n;i++){
		p[i].id = id[i];
		p[i].at = at[i];
		p[i].bt = bt[i];
		p[i].remaint = bt[i];
		
	}
	srtf(n,p);
}

int main(){
	int n = 5;
	initialize(n);
	return 0;
}
