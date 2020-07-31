#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>

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

}
