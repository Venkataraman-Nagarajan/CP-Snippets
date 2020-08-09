#include <stdlib.h> 
#include<stdio.h>
#include<string.h>
 
void merge(char a[][20],int i1,int j1,int i2,int j2)
{
	char temp[50][20];	//array used for merging
	int i,j,k;
	i=i1;	//beginning of the first list
	j=i2;	//beginning of the second list
	k=0;
	
	while(i<=j1 && j<=j2)	//while elements in both lists
	{
		if(strcmp(a[i],a[j])<0)
			strcpy(temp[k++],a[i++]);
		else
			strcpy(temp[k++],a[j++]);
	}
	
	while(i<=j1)	//copy remaining elements of the first list
		strcpy(temp[k++],a[i++]);
		
	while(j<=j2)	//copy remaining elements of the second list
		strcpy(temp[k++],a[j++]);
		
	//Transfer elements from temp[] back to a[]
	for(i=i1,j=0;i<=j2;i++,j++)
		strcpy(a[i],temp[j]);
}

void mergesort(char a[][20],int i,int j)
{
	int mid;
		
	if(i<j)
	{
		mid=(i+j)/2;
		mergesort(a,i,mid);		//left recursion
		mergesort(a,mid+1,j);	//right recursion
		merge(a,i,mid,mid+1,j);	//merging of two sorted sub-arrays
	}
}

int fileSort() {
	char areas[100][20];
	FILE *fp;  
   	char buff[100];//creating char array to store data of file  
   	fp = fopen("areas.txt", "r+");  
   	FILE *fptr;
   	fptr = fopen("areas1.txt", "w+");
   	int i=0;
	while(fscanf(fp,"%s", buff)==1){  
   		strcpy(areas[i++],buff);
   	}  
   	
   	mergesort(areas,0,i-1);

   	if(fptr == NULL)
   	{
      	printf("Error!");
      	exit(1);
   	}
   	for(int j=0;j<i;j++) {
   		fprintf(fptr,"%s\n",areas[j]);
   	}
	fclose(fp); 
   	fclose(fptr);
   	remove("areas.txt");
   	rename("areas1.txt","areas.txt");
   	return 0;
}

void fileWrite(cabDetails *cab) {
	cabDetails buff;//creating char array to store data of file  
   	FILE *fp=fopen("cabs.txt","w+");
   	int count=0,i,x;
   	while(cab[count].carNo) {
   		buff = cab[count++];
   	    fprintf(fp,"%d %s %s %d %lf %lf\n",buff.carNo,buff.type,buff.Location,buff.no_of_trips,buff.Distance_travelled,buff.Pay);
   		//printf("\n%d %s %s %d %lf %lf",buff.carNo,buff.type,buff.Location,buff.no_of_trips,buff.Distance_travelled,buff.Pay);	
   	}  
   	
	   fclose(fp); 
}