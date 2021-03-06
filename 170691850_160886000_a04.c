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

	int customerNum, r1, r2, r3, r4;
} Customer;

void ProgramOutput(int ct);

int safetyCheck(int ct);

int fileRead(char* fileName, Customer** customer);

void runProgram(int ct);

void *runThread(void *thread);

void requestResource(int threadID, int r1, int r2, int r3, int r4, int ct);





//Variable Declaration



int avail[5];

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
			avail[i]=atoi(argv[i]);
		}
	}

	int val[2];

	int rw = fileRead(val)[0];

	int col = fileRead(val)[1];

	for (int i = 1; i < argc; i++) {
           avail[i-1] = atoi(argv[i]);
    }
    printf("Currently Available Resources : " );





    for(int i = 0; i < argc-1; i++){
            printf("%d ",avail[i]);
    }
    printf("Number of Customers: %d\n", n);

    printf("Currently Available Resources : " );


    int ct = fileRead(fileName,&max);

	request = (Customer*) malloc(sizeof(Customer) * ct);

    alloc = (Customer*) malloc(sizeof(Customer)*ct);

    for(i =0; i <ct;i++)

	{
		alloc[i].customerNum = max[i].customerNum;


		alloc[i].r1 = 0;

		alloc[i].r2 = 0;
		//
		alloc[i].r3 = 0;


		alloc[i].r4 = 0;



		request[i].customerNum = max[i].customerNum;

		request[i].r1 = max[i].r1;

		request[i].r2 = max[i].r2;
		//ss
		request[i].r3 = max[i].r3;
		request[i].r4 = max[i].r4;
	}

	printf("Number of Customers: %d\n", ct);

	printf("Currently avail resources: %d %d %d %d\n", avail[1],avail[2],avail[3],avail[4]);

	printf("Maximum Resources from file:\n");

	for (i = 0; i < ct; i++)
	{
		printf("%d, %d, %d, %d\n", max[i].r1,max[i].r2,max[i].r3,max[i].r4);
	}
	//variables
	char line[100];

	char cmd[2];

	int threadID=-1;

	int r1=-1;

	int r2=-1;

	int r3=-1;

	int r4=-1;



	//loop for intializing
	do {

		printf("Enter Command: ");
		fgets(line,100,stdin);
		char *ptr = strtok(line, " ");

		strcpy(cmd,ptr);

		int j = 0;
		//loop for case
		while(ptr!=NULL)
		{
			switch(j){
				case 1:
					threadID = atoi(ptr);
					break;
				case 2:
					r1 = atoi(ptr);
					break;
				case 3:
					r2 = atoi(ptr);
					break;
				case 4:
					r3 = atoi(ptr);
					break;
				default:
					r4 = atoi(ptr);
			}

			j++;
			ptr = strtok(NULL," ");
		}

		if (strstr(cmd,"RQ")!=NULL)
		{
			printf("process request function\n");
			printf("%s %d %d %d %d %d \n\n", cmd, threadID, r1,r2,r3,r4);



		}
		else if(strstr(cmd,"RL")!=NULL)
		{
			printf("process release function\n");
			printf("%s %d %d %d %d %d \n\n", cmd, threadID, r1,r2,r3,r4);
		}
		else if(strstr(cmd,"*")!=NULL)
		{
			printf("process/display current state\n");
			printf("%s\n\n", cmd);
			outputValues(ct);

		}
		else if(strstr(cmd,"RUN")!=NULL)
		{
			printf("run function\n");

			printf("%s\n\n", cmd);
			runProgram(ct);
		}
		else
		{
			printf("invalid: 'RQ,RL,* or RUN' are valid\n");
		}


    } while (1);


}

void requestResource(int TID, int r1, int r2, int r3, int r4, int ct)
	{
		if (r1<=rqd[TID].r1 && r2<=rqd[TID].r2 &&
		r3<=rqd[TID].r3 && r4<=rqd[TID].r4)
		{
			if(r1 <= avail[1] && r2 <= avail[2] &&
			r3 <= avail[3] && r4 <= avail[4])
			{

				avail[1] -= r1;
				avail[2] -= r2;
				avail[3] -= r3;
				avail[4] -= r4;


				alloc[TID].r1+= r1;
				alloc[TID].r2+= r2;
				alloc[TID].r3+= r3;
				alloc[TID].r4+= r4;

				rqd[TID].r1-= r1;
				rqd[TID].r2-= r2;
				rqd[TID].r3-= r3;
				rqd[TID].r4-= r4;

				int safe = safetyCheck(ct);

				if (safe == 0)
				{
					avail[1] += r1;
					avail[2] += r2;
					avail[3] += r3;
					avail[4] += r4;

					alloc[TID].r1-= r1;
					alloc[TID].r2-= r2;
					alloc[TID].r3-= r3;
					alloc[TID].r4-= r4;

					rqd[TID].r1+= r1;
					rqd[TID].r2+= r2;
					rqd[TID].r3+= r3;
					rqd[TID].r4+= r4;
					printf("insuffiecient resources, need to wait\n");
				}
				else
				{
					printf("request complete");
				}


			}
			else
			{
				printf("cant request resource");
			}

		}
		else
		{
			printf("cant request resource");
		}

return;
}

int fileRead(char* fileName, Customer** max) {

	FILE *file = fopen(fileName, "r");

	struct stat st;
	fstat(fileno(file), &st);
	char* fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';

	if (file != NULL) {
		char str[1000]; //string buffer
		while (fgets(str, sizeof(str), file) != NULL) //read lines
		{

			strncat(fileContent, str, strlen(str));

		}
		fclose(file);



	} else {
		perror(fileName); //error
		return -1;
	}
	char* command = NULL;
	int ct;

	char* fileCopy = (char*) malloc((strlen(fileContent) + 1) * sizeof(char));
	strcpy(fileCopy, fileContent);
	command = strtok(fileCopy, "\r\n");
	while (command != NULL) {
		ct++;
		command = strtok(NULL, "\r\n");
	}
	max = (Customer) malloc(sizeof(Customer) * ct);

	char* lines[ct];
	command = NULL;
	int i = 0;
	command = strtok(fileContent, "\r\n");
	while (command != NULL) {
		lines[i] = malloc(sizeof(command) * sizeof(char));
		strcpy(lines[i], command);
		i++;
		command = strtok(NULL, "\r\n");
	}

	for (int k = 0; k < ct; k++) {
		char* token = NULL;
		int j = 0;
		int cID = 0;
		token = strtok(lines[k], ",");
		while (token != NULL) {
			switch (j) {
			(*max)[k].customerNum = cID;
			cID++;
		case 0:
			(*max)[k].r1 = atoi(token);
			break;
		case 1:
			(*max)[k].r2 = atoi(token);
			break;
		case 2:
			(*max)[k].r3 = atoi(token);
			break;
		default:
			(*max)[k].r4 = atoi(token);

			}

			j++;
			token = strtok(NULL, ",");
		}
	}
	return ct;



}

void runProgram(int ct)
{

	int k=safetyCheck(ct);
	if (k==0)
	{
		printf("UNSAFE\n");
		return;
	}
	else{

		for (i=0;i<ct;i++){ //create and execute threads
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


void programOutput(int ct)

{
	printf("Currently avail rs: %d %d %d %d\n", avail[1],avail[2],avail[3],avail[4]);
	printf("Maximum Rs from file:\n");

	for (i=0; i<ct; i++)
	{
		printf("%d, %d, %d, %d\n", max[i].r1,max[i].r2,max[i].r3,max[i].r4);
	}

	printf("current alloc\n");
	for (i=0; i<ct; i++)
	{
		printf("%d, %d, %d, %d\n", alloc[i].r1,alloc[i].r2,alloc[i].r3,alloc[i].r4);
	}

	printf("still needed\n");
	for (i=0; i<ct; i++)
	{
		printf("%d, %d, %d, %d\n", rqd[i].r1,rqd[i].r2,rqd[i].r3,rqd[i].r4);
	}
	return;
}


int safetyCheck(int ct){
	int finish[5] = {1,1,1,1,1};

	int av_cp[5];

	Customer* alloc_dup = NULL;

	Customer* needed_dup = NULL;



	alloc_dup = (Customer*) malloc(sizeof(Customer)*ct);

	needed_dup = (Customer*) malloc(sizeof(Customer)*ct);

	int count_dup = ct;

	for(i=1;i<5;i++)




		av_cp[i] = avail[i];


	for(x =0; x <ct;x++)
	{

		alloc_dup[x].customerNum = max[x].customerNum;

		alloc_dup[x].r1 = alloc[x].r1;

		alloc_dup[x].r2 = alloc[x].r2;

		alloc_dup[x].r3 = alloc[x].r3;

		alloc_dup[x].r4 = alloc[x].r4;

		needed_dup[x].customerNum = max[x].customerNum;

		needed_dup[x].r1 = rqd[x].r1;

		needed_dup[x].r2 = rqd[x].r2;

		needed_dup[x].r3 = rqd[x].r3;

		needed_dup[x].r4 = rqd[x].r4;
	}

	int sf = 0;
	int ck = 0;
	int y;
	while(count_dup>0)
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
						if (needed_dup[x].r1 > av_cp[y]) {
							ck = 0;
							break;
						}
					}
					if (y ==1)
					{
						if (needed_dup[x].r2 > av_cp[y]) {
							ck = 0;
							break;
						}
					}
					if( y ==2)
					{

						if (needed_dup[x].r3 > av_cp[y]) {

							ck = 0;
							break;
						}
					}
					if (y ==3)
					{

						if (needed_dup[x].r4 > av_cp[y]) {

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
