#include<stdio.h>
#include<stdlib.h>
#include<wait.h>

#define MAX 20

typedef struct process{
	int id;
	int prt;
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
gannt g1[MAX],g2[MAX];
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
			if(p[j].prt < p[i].prt){
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
	gannt gtemp1,gtemp2;
	for(int i = 0;i < n;i++){
		for(int j = i;j < n;j++){
			if(p[j].id < p[i].id){
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
			if(g1[j].id < g1[i].id){
				gtemp1 = g1[j];
				g1[j] = g1[i];
				g1[i] = gtemp1; 
			}
			if(g2[j].id < g2[i].id){
				gtemp2 = g2[j];
				g2[j] = g2[i];
				g2[i] = gtemp2; 
			}
		}
	}
}
int calgannt(int n,int j,int time,int pos,pro p[n],gannt g[MAX]){
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
void display(int n,pro p[n],gannt g[MAX]){
	int i;
	printf("id \tprt\tat \tbt \tct \ttat\twt \trt \tGannt chart\n");
	for(i = 0;i < n;i++){
		printf("%d \t%d \t%d \t%d \t%d \t%d \t%d \t%d \t%d \n",p[i].id,p[i].prt,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt,g[i].time);
	}
}
void pre_prt(int n,pro p[n]){
	int i = 0,j = 0,pos = 0,count = 0;
	pro temp;
	int time = p[pos].at;
	bubblesort(n,p);
	do{
      		//j = calgannt(n,j,time,pos,p);
      		pos = arrange(n,time,p);
      		j = calgannt(n,j,time,pos,p,g1);
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
		p[i].rt = g1[i].time - p[i].at;
	}
	printf("Preemptive Priority\n");
	display(n,p,g1);
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
void n_pre_prt(int n,pro p[n]){
        int i = 0,j = 0,pos = 0,count = 0;
	pro temp;
	int time = p[pos].at;
	bubblesort(n,p);
	do{
      		//j = calgannt(n,j,time,pos,p);
      		pos = arrange(n,time,p);
      		j = calgannt(n,j,time,pos,p,g2);
      		p[pos].ct = time + p[pos].bt;
      		time = p[pos].ct;
      		p[pos].remaint = 0;
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
		p[i].rt = g2[i].time - p[i].at;
	}
	printf("Non-Preemptive Priority\n");
	display(n,p,g2);
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
	pro p1[n],p2[n];
	for(i = 0;i < n;i++){
		p1[i].ct = 0;
		p2[i].ct = 0;
	}
	int id[] = {1,2,3,4,5};
	int prt[] = {2,0,3,1,4};
	int at[] = {0,5,12,2,9};
	int bt[] = {11,28,2,10,16};
	for(i = 0;i < n;i++){
		p1[i].id = id[i];
		p1[i].prt = prt[i];
		p1[i].at = at[i];
		p1[i].bt = bt[i];
		p1[i].remaint = bt[i];
		
	}
	for(i = 0;i < n;i++){
		p2[i].id = id[i];
		p2[i].prt = prt[i];
		p2[i].at = at[i];
		p2[i].bt = bt[i];
		p2[i].remaint = bt[i];
		
	}
	pre_prt(n,p1);
	n_pre_prt(n,p2);
}

int main(){
	int n = 5;
	initialize(n);
	return 0;
}
