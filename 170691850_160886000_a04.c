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
char tmp[256];

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
	//Command Line Arguments
	if(argc <2){
		printf("Argument Not Found");
		exit(1);
	}
    
    int avail[4] = { 10, 5, 7, 8 }; // Available Resources 


    printf("Number of Customers: %d\n", n);
    
    //ask for currently avaialbe resources
    printf("Currently Available Resources : " );
    fgets(tmp,sizeof(tmp),stdin);

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

bool getSafeSeq() {
	// get safe sequence
        int tempRes[n];
        for(int i=0; i<n; i++) tempRes[i] = resources[i];

        bool finished[m];
        for(int i=0; i<m; i++) finished[i] = false;
        int nfinished=0;
        while(nfinished < m) {
                bool safe = false;

                for(int i=0; i<m; i++) {
                        if(!finished[i]) {
                                bool possible = true;

                                for(int j=0; j<n; j++)
                                        if(need[i][j] > tempRes[j]) {
                                                possible = false;
                                                break;
                                        }

                                if(possible) {
                                        for(int j=0; j<n; j++)
                                                tempRes[j] += allocated[i][j];
                                        safeSeq[nfinished] = i;
                                        finished[i] = true;
                                        ++nfinished;
                                        safe = true;
                                }
                        }
                }

                if(!safe) {
                        for(int k=0; k<m; k++) safeSeq[k] = -1;
                        return false; // no safe sequence found
                }
        }
        return true; // safe sequence found
}
