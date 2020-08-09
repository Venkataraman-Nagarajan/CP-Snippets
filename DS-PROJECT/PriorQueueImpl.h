#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct {
    double dist;
    int index;
}Distance;

typedef struct {
    Distance a[100000];
    int size;
    int capacity;
}pq;

pq* init(int max){
    pq *p=(pq*)malloc(sizeof(pq));
    p->a[0].dist=INT_MIN;
    p->a[1].dist=INT_MIN;
    p->size=0;
    p->capacity=max;  
    return p; 
}

int isFull(pq *p)  {return p->size==p->capacity;}
int isEmpty(pq *p) {return p->size==0;}

void insert(pq *p,Distance x) {
    if(isFull(p)){
        printf("Queue Full\n");
    }
    else{
        int i=p->size;
        p->a[++p->size]=x;
        while(p->a[i/2].dist>p->a[i].dist ) {
            Distance t=p->a[i/2];
            p->a[i/2]=p->a[i];
            p->a[i]=t;
            i/=2;
        }
    }
}

void dispPQ(pq *p,int in,int lvl) {
    int i;
    for(int i=0;i<lvl;i++) printf("--");
    if(in<=p->size) { 
        printf("(%d)-(%.2lf)\n",p->a[in].index,p->a[in].dist);
        if(2*in <= p->size) dispPQ(p,2*in,lvl+1);
        if(2*in+1 <=p->size)  dispPQ(p,2*in+1,lvl+1);
    }
}

Distance Delete(pq *p) {
    if(isEmpty(p)) { printf("Queue Empty\n"); return p->a[0];}
    else {
        int i,child;
        Distance min = p->a[1];
        Distance last = p->a[p->size--];
        
        for(i=1;(i*2)<=p->size;i=child) {
            child=i*2;
            if(child+1<=p->size && p->a[child+1].dist<p->a[child].dist) child++;
            if(last.dist > p->a[child].dist)  p->a[i]=p->a[child];
            else break;
        }
        p->a[i]=last;
        return min;
    }   
}

