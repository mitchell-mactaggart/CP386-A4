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

int fileRead(char* fileName, Customer** customer);
int safetyCheck(int count);
void requestResource(int threadID, int resource1, int resource2, int resource3, int resource4, int count);
void releaseResource(int threadID, int resource1, int resource2, int resource3, int resource4);
void ProgramOutput(int count);
void runProgram(int count);
void *runThread(void *thread);

int available[5];
int i;
int safeSeq[5];
Customer* max;
Customer* alloc;
Customer* request; 

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

	int count = fileRead(fileName,&max);

	alloc = (Customer*) malloc(sizeof(Customer)*count);
	requested = (Customer*) malloc(sizeof(Customer)*count);
	for(i =0; i <count;i++)
	{
		alloc[i].customerNum = max[i].customerNum;
		alloc[i].resource1 = 0;
		alloc[i].resource2 = 0;
		alloc[i].resource3 = 0;
		alloc[i].resource4 = 0;

		requested[i].customerNum = max[i].customerNum;
		requested[i].resource1 = max[i].resource1;
		requested[i].resource2 = max[i].resource2;
		requested[i].resource3 = max[i].resource3;
		requested[i].resource4 = max[i].resource4;
	}

	printf("Number of Customers: %d\n",count);

	printf("Currently available resources: %d %d %d %d\n", available[1],available[2],available[3],available[4]);

	printf("Maximum Resources from file:\n");

	for (i=0; i<count; i++)
	{
		printf("%d, %d, %d, %d\n", max[i].resource1,max[i].resource2,max[i].resource3,max[i].resource4);
	}
	

	
	char line[100];
	char cmd[2];
	int threadID=-1;
	int resource1=-1;
	int resource2=-1;
	int resource3=-1;
	int resource4=-1;

	
	do {
        
		printf("Enter Command: ");
		fgets(line,100,stdin);


		char *ptr = strtok(line, " ");

		strcpy(cmd,ptr);

		int j =0;
		while(ptr!=NULL)
		{
			switch(j){
				case 1:
					threadID = atoi(ptr);
					break;
				case 2:
					resource1 = atoi(ptr);
					break;
				case 3:
					resource2 = atoi(ptr);
					break;
				case 4:
					resource3 = atoi(ptr);
					break;
				default:
					resource4 = atoi(ptr);
			}
			
			j++;
			ptr = strtok(NULL," ");
		}
		
		if (strstr(cmd,"RQ")!=NULL)
		{
			printf("process request function\n");
			printf("%s %d %d %d %d %d \n\n", cmd, threadID, resource1,resource2,resource3,resource4);
			requestResource(threadID,resource1,resource2,resource3,resource4,count);
			

		}
		else if(strstr(cmd,"RL")!=NULL)
		{
			printf("process release function\n");
			printf("%s %d %d %d %d %d \n\n", cmd, threadID, resource1,resource2,resource3,resource4);
			releaseResource(threadID,resource1,resource2,resource3,resource4);
		}
		else if(strstr(cmd,"*")!=NULL)
		{
			printf("process/display current state\n");
			printf("%s\n\n", cmd);
			outputValues(count);

		}
		else if(strstr(cmd,"RUN")!=NULL)
		{
			printf("run function\n");

			printf("%s\n\n", cmd);
			runProgram(count);
		}		
		else
		{
			printf("invalid: 'RQ,RL,* or RUN' are valid\n");
		}
		

    } while (1);

}

/*readFile function will take in a filename and read and return
its contents for the bankers algorithm
*/
int readFile(char* fileName, Customer** max)
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

/* runProgram will use safety algorithm to implement the program.
we will use this function to call requestResource, releaseResource and outputValues
depending on what command the user types: "RL, RQ or *"
*/
void runProgram(int count)
{

	int k=safetyAlgorithm(count);
	if (k==0)
	{
		printf("UNSAFE\n");
		return;
	}
	else{

		for (i=0;i<count;i++){ //create and execute threads
			int runnable = safeSeq[i];

			pthread_t threadID;
			pthread_attr_t newThread;
			pthread_attr_init(&newThread);

			pthread_create(&threadID, &newThread, runThread, (void *)&runnable);


			pthread_join(threadID, NULL);
		}
	}
	

	return;

}

void *runThread(void *thread)
{
	int *tid = (int*)thread;

	printf("-> Customer #: %d\n", *tid);

	printf("	Allocated Resources: ");
	printf("%d ",alloc[*tid].resource1);
	printf("%d ",alloc[*tid].resource2);
	printf("%d ",alloc[*tid].resource3);
	printf("%d\n",alloc[*tid].resource4);
	printf("	Needed Resources: ");
	printf("%d ",requested[*tid].resource1);
	printf("%d ",requested[*tid].resource2);
	printf("%d ",requested[*tid].resource3);
	printf("%d\n",requested[*tid].resource4);
	printf("	Available Resources: ");
	printf("%d ",available[1]);
	printf("%d ",available[2]);
	printf("%d ",available[3]);
	printf("%d\n",available[4]);

	printf("	Thread has started \n");
	sleep(2);
	printf("	Thread has finished \n");
	sleep(2);
	printf("	Thread is releasing resources \n");

	printf("	NEW AVAILABLE: ");

	available[1]+=alloc[*tid].resource1;
	printf("%d ",available[1]);
	available[2]+=alloc[*tid].resource2;
	printf("%d ",available[2]);
	available[3]+=alloc[*tid].resource3;
	printf("%d ",available[3]);
	available[4]+=alloc[*tid].resource4;
	printf("%d\n\n",available[4]);
    sleep(2);

	alloc[0].resource1=0;
	alloc[1].resource2=0;
	alloc[2].resource3=0;
	alloc[3].resource4=0;

	requested[0].resource1 = max[0].resource1;
	requested[1].resource2 = max[1].resource2;
	requested[2].resource3 = max[2].resource3;
	requested[3].resource4 = max[3].resource4;

	pthread_exit(0);

}

/* Will fill an allocation array, then we will use saftey algorithm and
output whether the request was satisfied or denied by using 0 for sucess and -1 
for denied.  Command will look like this:
RQ cus# th# th# th# th#
example: RQ 0 3 1 2 1 (from assignment)
*/
void requestResource(int threadID, int resource1, int resource2, int resource3, int resource4, int count)
{
	if (resource1<=requested[threadID].resource1 && resource2<=requested[threadID].resource2 &&
	resource3<=requested[threadID].resource3 && resource4<=requested[threadID].resource4)	
	{
		if(resource1 <= available[1] && resource2 <= available[2] && 
		resource3 <= available[3] && resource4 <= available[4])
		{

			available[1] -= resource1;
			available[2] -= resource2;
			available[3] -= resource3;
			available[4] -= resource4;


			alloc[threadID].resource1+= resource1;
			alloc[threadID].resource2+= resource2;
			alloc[threadID].resource3+= resource3;
			alloc[threadID].resource4+= resource4;

			requested[threadID].resource1-= resource1;
			requested[threadID].resource2-= resource2;
			requested[threadID].resource3-= resource3;
			requested[threadID].resource4-= resource4;

			int safe = safetyAlgorithm(count);

			if (safe == 0)
			{
				available[1] += resource1;
				available[2] += resource2;
				available[3] += resource3;
				available[4] += resource4;

				alloc[threadID].resource1-= resource1;
				alloc[threadID].resource2-= resource2;
				alloc[threadID].resource3-= resource3;
				alloc[threadID].resource4-= resource4;

				requested[threadID].resource1+= resource1;
				requested[threadID].resource2+= resource2;
				requested[threadID].resource3+= resource3;
				requested[threadID].resource4+= resource4;	
				printf("insuffiecient resources, need to wait\n");
			}
			else
			{
				printf("request completed sucessfully\n");
			}
			

		}
		else
		{
			printf("can not request more than available resources\n");
		}
		
	}
	else
	{
		printf("can not request more than needed resources\n");
	}
	

	return;
}

void releaseResource(int threadID, int resource1, int resource2, int resource3, int resource4)
{
	if (resource1<=alloc[threadID].resource1 && resource2<=alloc[threadID].resource2 &&
	resource3<=alloc[threadID].resource3 && resource4<=alloc[threadID].resource4)
	{
		available[1] += resource1;
		available[2] += resource2;
		available[3] += resource3;
		available[4] += resource4;

		alloc[threadID].resource1-= resource1;
		alloc[threadID].resource2-= resource2;
		alloc[threadID].resource3-= resource3;
		alloc[threadID].resource4-= resource4;

		requested[threadID].resource1+= resource1;
		requested[threadID].resource2+= resource2;
		requested[threadID].resource3+= resource3;
		requested[threadID].resource4+= resource4;
		printf("resources released sucessfully\n");
	}
	else
	{
		printf("can not release more than allocated resources\n");
	}
	
	return;
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


int safetyCheck(int count)

{
	
	int finish[5] = {1,1,1,1,1};
	int available_copy[5];
	Customer* alloc_copy = NULL;

	Customer* needed_copy = NULL;
	alloc_copy = (Customer*) malloc(sizeof(Customer)*count);
	needed_copy = (Customer*) malloc(sizeof(Customer)*count);
	int count_Copy = count;

	for(i=1;i<5;i++)
		available_copy[i] = available[i];



	

	for(i =0; i <count;i++)
	{
		
		alloc_copy[i].customerNum = max[i].customerNum;
		alloc_copy[i].resource1 = alloc[i].resource1;
		alloc_copy[i].resource2 = alloc[i].resource2;
		alloc_copy[i].resource3 = alloc[i].resource3;
		alloc_copy[i].resource4 = alloc[i].resource4;
		
		needed_copy[i].customerNum = max[i].customerNum;
		needed_copy[i].resource1 = requested[i].resource1;
		needed_copy[i].resource2 = requested[i].resource2;
		needed_copy[i].resource3 = requested[i].resource3;
		needed_copy[i].resource4 = requested[i].resource4;
	}
	int safe = 0;
	int check = 0;
	int j;

	
	while(count_Copy>0)
	{
		safe = 0;
		for(i=0;i<5;i++)
		{
			if (finish[i]==1)
			{
				check = 1;
				for (j=1;j<5;j++)
				{
					if (j ==0)
					{
						if (needed_copy[i].resource1 > available_copy[j]) {
							check = 0;
							break;
						}
					}
					if (j ==1)
					{
						if (needed_copy[i].resource2 > available_copy[j]) {
							check = 0;
							break;
						}
					}
					if( j ==2)
					{
						if (needed_copy[i].resource3 > available_copy[j]) {
							check = 0;
							break;
						}
					}
					if (j ==3)
					{
						if (needed_copy[i].resource4 > available_copy[j]) {
							check = 0;
							break;
						}
					}
				}

				if (check==1) {
					finish[i] = 0;
					safeSeq[(5-count_Copy)] = i;
					count_Copy--;
					safe = 1;

					for (j = 1; j < 5; j++){
						

						switch(j)
						{
							case 0:
								available_copy[j] += alloc_copy[i].resource1;
								break;
							
							case 1:
								available_copy[j] += alloc_copy[i].resource2;
								break;
							case 2:
								available_copy[j] += alloc_copy[i].resource3;
								break;
							case 3:
								available_copy[j] += alloc_copy[i].resource4;
								break;
								
						}		
					}
					break;
				}
			}
			
		}

		if (safe == 0)
		{
			printf("not safe\n");
			break;
		}
	
	}



	return safe;
}