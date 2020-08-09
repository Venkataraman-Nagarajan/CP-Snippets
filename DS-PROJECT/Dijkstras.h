#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "PriorQueueImpl.h"

static int cur_state = -1;
	
typedef struct nodes {
	int data;
	struct nodes *next;
}nodes;

typedef struct  {
	int carNo;
	char type[7],Location[20];
	int no_of_trips;
	double Distance_travelled,Pay;
}cabDetails;

typedef struct { 
	int visited;
	int isCab; 
	double cost[100],dist;
}graph;

typedef struct {
	int no_of_cities;
	nodes *node[100];
	char cities[100][20];
}cityADT;


int max(int a, int b) {
	return a>b?a:b;
}

int min(int a,int b) {
	return a<b?a:b;
}

int findCity(cityADT *c,char* city) {
	int b=0,l=min(c->no_of_cities-1,cur_state),m;
	while(b<=l) {
		m =(b+l)/2;
		if(strcmp(city,c->cities[m])==0)	return m;
		else if(strcmp(city,c->cities[m])<0) l=m-1;
		else	b=m+1;
	}
	return -1;
}


void dispCity(cityADT *c) {
	int i,j;
	for(i=0;i<=min(c->no_of_cities-1,cur_state);i++) {
		printf("%-10s connects -> | ",c->cities[i]);
		nodes *n = c->node[i];
		while(n!=NULL) {
			printf("%-10s | ",c->cities[n->data]);
			n=n->next;
		}
		printf("\n");
	}
}


cabDetails* fileReader(cityADT *c,graph *g)
{
   	cabDetails *cab=(cabDetails*)malloc(100*sizeof(cabDetails));	
   	cabDetails buff;//creating char array to store data of file  
   	FILE *fp=fopen("cabs.txt","r+");
   	int count=0,i,x;
   	while(fscanf(fp,"%d %s %s %d %lf %lf\n",&buff.carNo,buff.type,buff.Location,&buff.no_of_trips,&buff.Distance_travelled,&buff.Pay)==6) {
   	  cab[count++]=buff;
   	  int y = findCity(c,buff.Location);
   	  if(y!=-1) {
   	  	g[y].isCab+=1;
   	  }
   	}  
	fclose(fp); 
	return cab;
}

void disp(cabDetails *c) {
	printf("\n------------------------------------------------------------------\n");
	printf("| CNO | TYPE   |    LOCATION     | NO. TRIPS | DIST(km) |   PAY  |\n");
	printf("------------------------------------------------------------------\n");
	int i=0;
	while(c[i].carNo) {
		printf("| %2d  | %-5s  | %-15s | %9d | %8.2lf | %6.1lf |\n",c[i].carNo,c[i].type,c[i].Location,c[i].no_of_trips,c[i].Distance_travelled,c[i].Pay);
		i++;
	}
	printf("------------------------------------------------------------------\n");	
}

cityADT* Starter() {
	cityADT *c = (cityADT*)malloc(sizeof(cityADT));
	FILE *fp;  
   	char buff[100];//creating char array to store data of file  
   	fp = fopen("areas.txt", "r+");  
   	int i=0;
   	c->no_of_cities=0;
   	cur_state++;
	while(fscanf(fp,"%s", buff)==1){  
   		strcpy(c->cities[i++],buff);
   		c->no_of_cities++;
   		cur_state++;
   	}
   	fclose(fp);  

   	for(int i=0;i<100;i++) {
   		c->node[i]=(nodes*)malloc(sizeof(nodes));
   		c->node[i]->data=i;
   		c->node[i]->next=NULL;
   	}
   	
   	FILE *fp1 = fopen("Map.txt","r+");
   	double a[100];
   	char s[100][100],d[100][100];
   	i=0;
   	while(fscanf(fp1,"%s %s %lf\n",s[i],d[i],&a[i])==3) {
   		int x = findCity(c,s[i]);
   		int y = findCity(c,d[i]);

   		if(x!=-1 && y!=-1) {
   			nodes *temp = (nodes*)malloc(sizeof(nodes));
   			temp->data = y;
   			temp->next=c->node[x]->next;
   			c->node[x]->next = temp;

   			nodes *temp1 = (nodes*)malloc(sizeof(nodes));
   			temp1->data = x;
   			temp1->next=c->node[y]->next;
   			c->node[y]->next = temp1;
   			i++;
   		}
   	}
   	fclose(fp);
   	return c;
}

graph* begin(cityADT* c) {
	graph *g =(graph*)malloc(100*sizeof(graph));
	FILE *fp = fopen("Map.txt","r+");
   	char s[100],d[100];

   	for(int i=0;i<100;i++) {
   		g[i].dist=INT_MAX;
   		g[i].visited=0;
   		g[i].isCab = 0;
   		for(int j=0;j<100;j++) {
   			if(i!=j) g[i].cost[j] =INT_MAX;
   			else	 g[i].cost[j] =0;
   		}
   	}

   	double i;
   	while(fscanf(fp,"%s %s %lf\n",s,d,&i)==3) {
   		int x = findCity(c,s);
   		int y = findCity(c,d);

   		if(x!=-1 && y!=-1) {
   			g[x].cost[y]=g[y].cost[x]=i;
   		}
   	}
   	fclose(fp);
   	return g;
}

void makeZero(graph *g) {
	int i;
	for(i=0;i<100;i++) g[i].visited=0;
}

void visit(graph *g,int x) {
	g[x].visited=1;
}

int unvisited(cityADT *c,graph *g) {
	int i;
	for(i=0;i<=min(c->no_of_cities-1,cur_state);i++) {
		if(g[i].visited==0)
			return i;
	}
	return -1;
}

int minUnvisited(cityADT *c,graph *g) {
	int Min=INT_MAX,i,pos=-1;
	for(i=0;i<=min(c->no_of_cities-1,cur_state);i++) {
		if(!g[i].visited && Min>=g[i].dist) {
			Min=g[i].dist;
			pos=i;
		}
	}
	return pos;
}


void setItUp(int x,graph *g,cityADT *c) {
	g[x].dist=0;
	for(int i=0;i<c->no_of_cities;i++) {
		if(i!=x)
			g[i].dist = INT_MAX;
	}
}

void Dijkstras(cityADT *c,char *start,char *destination,graph *g,cabDetails *cab) {
	makeZero(g);
	pq *p = init(c->no_of_cities);
	int begin = findCity(c,start);
	int end = findCity(c,destination);
	setItUp(begin,g,c);
	int v,w;
	while(unvisited(c,g)+1) {
		v=minUnvisited(c,g);
		visit(g,v);
		Distance x;
		x.dist=g[v].dist;x.index=v;
		insert(p,x);
		nodes *n = c->node[v];
		while(n!=NULL) {
			if(g[n->data].visited==0) {
				/*
				if(g[n->data].dist > g[c->node[v]->data].dist+g[n->data].cost[c->node[v]->data]) {
					g[n->data].dist = g[c->node[v]->data].dist+g[n->data].cost[c->node[v]->data];
				}*/
				g[n->data].dist = min(g[n->data].dist,g[c->node[v]->data].dist+g[n->data].cost[c->node[v]->data]);
			}
			n=n->next;
		}
	}

	int flag=1;
	if(g[begin].visited != g[end].visited)  {
		printf("\n\n SORRY !! SERVICE NOT AVAILABLE\n\n");
		return;
	}
	else {
		while(!isEmpty(p)) {
			Distance x = Delete(p);
			if(x.dist < 10 && g[x.index].isCab) {
				g[x.index].isCab--;
				int i=0;
				while(cab[i].carNo) {
					if(x.index == findCity(c,cab[i].Location)) {
						//printf("\n%lf - %lf ",g[begin].dist,g[end].dist);
						cab[i].Distance_travelled += g[x.index].dist + g[end].dist;
						strcpy(cab[i].Location , destination);
						int y = cab[i].Pay;
						cab[i].Pay += max(100,100 + 6*(g[end].dist-5));
						cab[i].no_of_trips+=1;
						printf("\n\n RIDE SUCCESSFUL \n\n");
						printf("\nTRIP DETAILS :\n  CAB NO - %d\n  SOURCE - %s\n  DESTINATION - %s\n  TYPE - %s\n  COST - %-.2lf\n\n",cab[i].carNo,start,destination,cab[i].type,cab[i].Pay - y);
						//printf("\nTRIP DETAILS :\n\t%-12s%d\n\t%-12s%s\n\t%-12s%s\n\t%-12s%s ","CAB NO -",cab[i].carNo,"SOURCE",start,"DESTINATION",destination,"TYPE",cab[i].type);
						flag=0;
						break;
					}
					i++;
				}
				break;
			}
		}
	}
	if(flag) {printf("\n\n NO CABS AVAILABLE NEARBY\n\n");}
}
