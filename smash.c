#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#include "smash.h"	//contains prototypes for implemented functions
#include "history.h"//contains prototyope for histoy commands 
//#include "commands.c" //this line was not needed to execute successfully

#define MAXLINE 4096
#endif /*CONFIG_H*/

//----------------
//main -- takes user input and calles appropriate functuion
//0 --normal
//
//----------------

int NumCommands =0; //track the total number of commands given

int main(int argc, char**argv){
  int eStatus = 0;
  char bfr[MAXLINE];
  init_history();
  //temp history test
  //  add_history("hello",0);
  //  print_history(1);
  //
  
  fputs("$ ", stderr);
  while(fgets(bfr,MAXLINE,stdin)){
    bfr[strlen(bfr)-1]='\0'; //replace newline with null terminator
    
    executeCommand(bfr); 
    //int temp; 
    
  }
  fputs("\n", stdout);//i just want to end the line thats it. 
  
  
  
  return eStatus; 
}



