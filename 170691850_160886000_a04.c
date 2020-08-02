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

void ProgramOutput(int count);

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

        printf("Following is the SAFE Sequence\n"); 
    for (i = 0; i < n - 1; i++) 
        printf(" P%d ->", ans[i]); 
    printf(" P%d", ans[n - 1]); 
  
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