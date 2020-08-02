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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "headers.h"

//Variable Declaration
int n, m, i, j, k, *safeSeq;
int MAX = 200;

int bankers_algoithm(){

    int f[n], ans[n], ind = 0; 
    for (k = 0; k < n; k++) { 
        f[k] = 0; 
    } 
    int need[n][m]; 
    for (i = 0; i < n; i++) { 
        for (j = 0; j < m; j++) 
            need[i][j] = max[i][j] - alloc[i][j]; 
    } 
    int y = 0; 
    for (k = 0; k < 5; k++) { 
        for (i = 0; i < n; i++) { 
            if (f[i] == 0) { 
  
                int flag = 0; 
                for (j = 0; j < m; j++) { 
                    if (need[i][j] > avail[j]){ 
                        flag = 1; 
                         break; 
                    } 
                } 
  
                if (flag == 0) { 
                    ans[ind++] = i; 
                    for (y = 0; y < m; y++) 
                        avail[y] += alloc[i][y]; 
                    f[i] = 1; 
                } 
            } 
        } 
    } 
  
    return (0); 

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
	int avail[MAX]
	//Command Line Arguments
	if(argc <2){
		printf("Argument Not Found");
		exit(1);
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



int safetyCheck(int count){
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
