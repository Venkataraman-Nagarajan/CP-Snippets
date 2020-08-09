#include<stdio.h>
#include<string.h>
typedef struct cabDetails{
	int carNo;
	char type[50],Location[50];
	int no_of_trips;
	double Distance_travelled,Pay;
}cabDetails;

int main()
{
   	cabDetails *cab;	
   	cabDetails buff;//creating char array to store data of file  
   	FILE *fp=fopen("cabs.txt","r+");
   	int count=0,i,x;
   	while(fscanf(fp,"%d %s %s %d %lf %lf\n",&buff.carNo,buff.type,buff.Location,&buff.no_of_trips,&buff.Distance_travelled,&buff.Pay)==6) {
   	  cab[count++]=buff;
   		printf("\n%d %s %s %d %lf %lf",buff.carNo,buff.type,buff.Location,buff.no_of_trips,buff.Distance_travelled,buff.Pay);	
   	}  
   	
	   fclose(fp); 
      return 0;
}
