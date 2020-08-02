/*
Name: Hassan Siddiqui
Email: sidd1850@mylaurier.ca
Student ID: 170691850
Github Username: Sidd1850

Name: Mitchell MacTaggart
Email: mact6000@mylaurier.ca
Student ID: 160886000
GitHub Username: mitchell-macTaggart
*/

#include<stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>


typedef struct customer
{
	int customerNum, resource1, resource2, resource3, resource4;
} Customer;

void ProgramOutput(int count);
int safetyCheck(int count);
int fileRead(char* fileName, Customer** customer);


//Variable Declaration
int available[5];
int i;
int safeSeq[5];
Customer* max;
Customer* alloc;
Customer* request; 


int fileRead(char* fileName, Customer** max)
{
	
    FILE *file = fopen(fileName, "r");

	struct stat st;
	fstat(fileno(file), &st);
	char* fileContent = (char*)malloc(((int)st.st_size+1)* sizeof(char));
	fileContent[0]='\0';

	if (file != NULL)
	{
		char str[1000]; //string buffer
		while (fgets(str, sizeof(str), file) != NULL) //read lines
		{

            strncat(fileContent,str,strlen(str));
			
		}
		fclose(file);

		

	}
	else
	{
		perror(fileName); //error
        return -1;
	}
	char* command = NULL;
	int count;

	char* fileCopy = (char*)malloc((strlen(fileContent)+1)*sizeof(char));
	strcpy(fileCopy,fileContent);
	command = strtok(fileCopy,"\r\n");
	while(command!=NULL)
	{
		count++;
		command = strtok(NULL,"\r\n");
	}
	*max = (Customer*) malloc(sizeof(Customer)*count);

	char* lines[count];
	command = NULL;
	int i=0;
	command = strtok(fileContent,"\r\n");
	while(command!=NULL)
	{
		lines[i] = malloc(sizeof(command)*sizeof(char));
		strcpy(lines[i],command);
		i++;
		command = strtok(NULL,"\r\n");
	}

	for(int k=0; k<count; k++)
	{
		char* token = NULL;
		int j = 0;
		int cID=0;
		token =  strtok(lines[k],",");
		while(token!=NULL)
		{
			switch(j){
				(*max)[k].customerNum = cID;
				cID++;
				case 0:
					(*max)[k].resource1 = atoi(token);
					break;
				case 1:
					(*max)[k].resource2 = atoi(token);
					break;
				case 2:
					(*max)[k].resource3 = atoi(token);
					break;
				default:
					(*max)[k].resource4 = atoi(token);
					
			}
			
			j++;
			token = strtok(NULL,",");
		}
	}
	return count;
	

}


void request_resource(){
   sleep(1);
   return NULL;
}

void release_resource(){
  sleep(2);
  int alloc[5][4];
  return NULL;
}

void set_max_resources(){
    //Opening File.
    FILE * fp;
    fp = fopen("sample4_in.txt","r");

    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n')
            n = n + 1; 
    
    int max[n][4];
    int i,j;

    for(i=0; i<=n; i++) {
        for(j=0; j<12; j++) {
            fscanf(fp, " %i", &max[i][j]);;
        }
    }

}

int main(int argc, char *argv[]) 
{ 
	char *fileName ="sample4_in.txt";

	if(argc!=5)
	{
		printf("INVALID: 4 values only\n");
		return -1;
	}
	else
	{
		for (i=1; i<argc; i++)
		{
			available[i]=atoi(argv[i]);
		}
	}
    
    
    //Takes user input on available resources from command line in string and converts to int
    for(int i = 1; i < argc; i++){
           avail[i-1] = atoi(argv[i]);
    }
    //Prints Available Resources
    printf("Currently Available Resources : " );
    for(int i = 0; i < argc-1; i++){
            printf("%d ",available[i]);
    }
    printf("Number of Customers: %d\n", n);
    
    //ask for currently avaialbe resources
    printf("Currently Available Resources : " );

    printf("Maximum resources from file:\n");
    for(i=0; i<m; i++) {
        for(j=0; j<n; j++) {
            printf("%c",max[i][j]);
        }
    }

    printf("Enter Command:");
    scanf("%s",command);
    printf("%s \n",command);

}

void programOutput(int count)

{
	printf("Currently available resources: %d %d %d %d\n", available[1],available[2],available[3],available[4]);
	printf("Maximum Resources from file:\n");

	for (i=0; i<count; i++)
	{
		printf("%d, %d, %d, %d\n", max[i].resource1,max[i].resource2,max[i].resource3,max[i].resource4);
	}

	printf("current alloc\n");
	for (i=0; i<count; i++)
	{
		printf("%d, %d, %d, %d\n", alloc[i].resource1,alloc[i].resource2,alloc[i].resource3,alloc[i].resource4);
	}

	printf("still needed\n");
	for (i=0; i<count; i++)
	{
		printf("%d, %d, %d, %d\n", requested[i].resource1,requested[i].resource2,requested[i].resource3,requested[i].resource4);
	}
	return;
}


int safetyCheck(int ct){
	int finish[5] = {1,1,1,1,1};
	
	int available_copy[5];
	
	Customer* alloc_copy = NULL;
	
	Customer* needed_copy = NULL;
	
	
	
	alloc_copy = (Customer*) malloc(sizeof(Customer)*ct);
	
	needed_copy = (Customer*) malloc(sizeof(Customer)*ct);
	
	int count_Copy = ct;
	
	for(i=1;i<5;i++)
		
		
		
		available_copy[i] = available[i];
	
	
	for(x =0; x <ct;x++)
	{
	
		alloc_copy[x].customerNum = max[x].customerNum;
		
		alloc_copy[x].resource1 = alloc[x].resource1;
		
		alloc_copy[x].resource2 = alloc[x].resource2;
		
		
		
		alloc_copy[x].resource3 = alloc[x].resource3;
		
		alloc_copy[x].resource4 = alloc[x].resource4;
		
		needed_copy[x].customerNum = max[x].customerNum;
		
		needed_copy[x].resource1 = requested[x].resource1;
		
		needed_copy[x].resource2 = requested[x].resource2;
		
		needed_copy[x].resource3 = requested[x].resource3;
		
		needed_copy[x].resource4 = requested[x].resource4;
	}
	
	int sf = 0;
	int ck = 0;
	int y;	
	while(count_Copy>0)
	{
		sf = 0;
		for(x=0;x<5;x++)
		{
			if (finish[x]==1)
			{
				ck = 1;
				for (y=1;y<5;y++)
				{
					if (y ==0)
					{
						if (needed_copy[x].resource1 > available_copy[y]) {
							ck = 0;
							break;
						}
					}
					if (y ==1)
					{
						if (needed_copy[x].resource2 > available_copy[y]) {
							ck = 0;
							break;
						}
					}
					if( y ==2)
					{
						if (needed_copy[x].resource3 > available_copy[y]) {
							ck = 0;
							break;
						}
					}
					if (y ==3)
					{
						if (needed_copy[x].resource4 > available_copy[y]) {
							ck = 0;
							break;
						}
					}
				}
			}	
		}
		if (sf == 0)
	
		{
		
			printf("not safe\n");
			
			break;
		}
	}
	
	return sf;
}
