#define MAXHISTORY 10
#define MAXLINE 4096
#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaire array for history
struct Cmd history[MAXHISTORY]; 
// this will be used to count how many arguments are stored in cmd
// use mod 10 to store new history.
int head = 0; 
int counter = 0; 


// builds data structures for recording cmd history
void init_history(void){
  int i;
  for(i=0;i<10;i++){
      history[i].cmd = (char*)malloc(MAXLINE);
      
    }
  }
  
//add entry to the history array
void add_history(char * cmd, int exitStatus){
  int temp = counter %10; 
  strcpy(history[temp].cmd,cmd);
  history[temp].exitStatus = exitStatus;
  counter++;
  if(counter > 10)
  {
    head = (head+1)%10; //[0,9]
  }
}
//print all entries in history
void print_history(int fSN){
  if(counter <10){
    for(int i =0; i<counter;i++){
      printf("%d [%d] ",(fSN+i),history[i].exitStatus);
      puts(history[i].cmd);
      //printf("\n");
    }
  }
  else{
  int temp =0;
    for(int i=0; i < 10; i++){
      temp = (head + i)%10;
      printf("%d [%d] %s\n",(fSN +i),history[temp].exitStatus, history[temp].cmd);
    }
  }
  
}
void set_status(int exitS)
{
  int temp = (counter -1)%10;
  history[temp].exitStatus = exitS;
}

//free all memeory from history
void clear_history(void){
   int i;
  for(i=0;i<10;i++){
    //
    free(history[i].cmd);
     //free(history[i].exitStatus);
    }
    //free(history);
}