#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <string.h>

void request_resource(){
   sleep(1);
   return NULL;
}

void release_resource(){
  sleep(2);
  return NULL;
}

int main() 
{
    int n, m, i, j, k; 
    n = 0; // Number of processes 
    m = 3; // Number of resources 

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

    int avail[4] = { 10, 5, 7, 8 }; // Available Resources 
  
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
