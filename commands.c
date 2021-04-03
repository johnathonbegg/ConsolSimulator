#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#include <unistd.h>  //for chdir() comamnd
#include <sys/types.h> 
#include <sys/wait.h> 
#include "history.h"
#define MAXLINE 4096



void executeExternalCommand(char * str){
  char* commandArgs[1025];
  char* token = strtok(str," "); 
  int numTokens = 0;
  //printf("attempting to execute external: %s\n", str);
  
  while (token!= NULL && numTokens < 1024){
    commandArgs[numTokens] = token; 
    numTokens +=1; 
    
    token = strtok(NULL," ");
    
  }
  //set last arg to null
  commandArgs[numTokens] = NULL; 
  
  //printf("processing\n");
  execvp(commandArgs[0],commandArgs);
  perror(commandArgs[0]);
  exit(127);
  
}



void executeCommand(char *str){
  
  extern int NumCommands; 
  NumCommands +=1; 
  
  char* commandStr; 
  commandStr = (char*)malloc(MAXLINE);
  strncpy(commandStr,str,MAXLINE);
  
  int i =0; 
  int count =0; //count number of tokens i create
  char *args[MAXLINE]; //no possiblity of more than 4096 characters
  char *token; 
  char eMessage[MAXLINE]; 
  int errorN = 0;
  add_history(str, errorN);
  
  token = strtok(str, " "); //tokenize on space
  while(token != NULL)
  {
    args[i] = token; 
    token = strtok(NULL, " "); 
    i++;
    count++; 
  }
   i =0; 
  //Exit COmmand ==============================================================
  if(strcmp(args[0], "exit")==0)
  {
    fputs("Closing\n", stdout); 
    //free memory before exit
    free(commandStr);
    clear_history();
    exit(0); 
  }
  //Change Directrory command
  if(strcmp(args[0], "cd")==0)
  {
    //printf("testing\n");
    if(count == 2)//this will not work if there are not at least 2 args. 
    {
      //snprintf(command,MAXLINE, "chdir %s", args[1]);
      if(chdir(args[1]) != 0)
      {
      snprintf(eMessage, MAXLINE, "%s: No such file or directory\n", args[1]);
        fputs(eMessage,stderr); 
        errorN =-1;
      }
    }
    else
    {
      snprintf(eMessage, MAXLINE, "Error: Invalid command\n");
      fputs(eMessage, stderr);
    }
    //printf("\n");
    //system("ls"); 
   
  }
  
  //TODO external commands ----------------------------------------
  else if(strcmp(args[0],"history")!=0){
    //errorN = 127;
    //printf("command not yet implemented: %s\n",commandStr);
    pid_t pid = fork();
    //0 - child process
    //else parent
    if(pid==0){
      executeExternalCommand(commandStr);
    }
    else{
       wait(&errorN);
    }
    
    if(WIFEXITED(errorN))
    {
      //printf("Exit status: %d\n", WEXITSTATUS(errorN));
      errorN = WEXITSTATUS(errorN);
    }
    
    
  }
  
  //temporaty print all args
  /*else
  {
  
  while(i < count)
   {
     printf("[%d] %s\n",i,args[i]); 
     i++;
   }
  }*/
  
  //add_history(command, errorN);
  set_status(errorN);
  if(strcmp(args[0], "history")==0){
    //temporaty implementation
   if(NumCommands < 10){
    print_history(1);
   }
   else{
     print_history(NumCommands-9);
   }
   
  }
  free(commandStr);
  fputs("$ ", stderr); 
  
}
