#include "Dijkstras.h"
#include "fileWrite.h"

void startThis() {
	system("clear");
	printf("\n\t\t\tCAB SIMULATOR\n\t\t\t^^^^^^^^^^^^^");
	printf("\n\t\t    ( DS - MINI PROJECT )");
	printf("\n\n TEAM: \n\t - VISHAL T\n\t - VAISHNAVI M R\n\t - VENKATARAMAN N\n");
	printf("\n\nPress ENTER to continue ... ");
	getchar();
	system("clear");
}

int main() {
	startThis();
	KickStart:
	system("clear");
	fileSort();
	cityADT *c = Starter();
	graph *g = begin(c);
	cabDetails *cab = fileReader(c,g);
	
	int choice;
	char m; 
	do {
		system("clear");
		printf("\n\n\t\t\tVVV CAB SERVICE - ADMIN CENTRE\n\n");
		printf(" OPTIONS - \n\t 1 - BOOK A RIDE\n\t 2 - VEIW CAB PROFILE\n\t 3 - UPDATE INFO\n\t 0 - CLOSE\n\n Enter your choice : ");
		scanf(" %c",&m);
		switch(m) {
			case '1' : {
				char source[100];
				char destination[100];
				system("clear");
				printf("\n\n\n\n\t\t\tBOOK A RIDE\n\t\t\t^^^^^^^^^^^^^\n\n\t\tSTARTING POINT    : ");
				scanf("%s",source);
				int x = findCity(c,source);
				if(x==-1) { printf("\n SORRY .. OUR CAB SERIVICE DO NOT EXTEND OVER THERE");  }
				else {
					printf("\t\tDESTINATION POINT : ");
					scanf("%s",destination);
					int y = findCity(c,destination);
					if(y==-1) { printf("\n SORRY .. OUR CAB SERIVICE DO NOT EXTEND OVER THERE");  }
					else {
						Dijkstras(c,source,destination,g,cab);
					}
				}
				getchar();
				break;
			}
			case '2' : {
				system("clear");
				printf("\n\n");
				disp(cab);
				getchar();
				break;
			}
			case '3' : {
				system("clear");
				printf("\n\n UPDATE FILES  ( if neccessary ) - [areas.txt , cabs.txt , Maps.txt ]\n\n Press ENTER to proceed ...\n");
				getchar();
				getchar();
				system("nano cabs.txt");
				system("clear");
				printf("\n\n\n Press ENTER to continue :.....");
				getchar();
				system("nano areas.txt");
				system("clear");
				printf("\n\n\n Press ENTER to continue :.....");
				getchar();
				system("nano Map.txt");
				system("clear");
				printf("\n\n Press ENTER to continue ...\n");
				getchar();
				fileWrite(cab);
				goto KickStart;
				break;
			}
		}
		if(m!='0' && (m>='1' && m<='3'))
		printf("\n\nPress ENTER to continue ... ");
		getchar();
	}while(m!='0');

	fileWrite(cab);	

	printf("\n\nPress ENTER to continue ... ");
	getchar();
	printf("\n");
	system("clear");
	return 0;
}