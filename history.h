#define MAXHISTORY 10

struct Cmd {
  char* cmd;        //saved copy of the user's Command String
  int exitStatus;   //saved copy of exit status
};

void init_history(void); // builds data structures for recording cmd history
void add_history(char * cmd, int exitStatus);//adds an entry to the history
void clear_history(void);//Frees all malloc'd memory in the history
void print_history(int firstSequenceNumber);//Prints the hostory to STD out
void set_status(int exitStatus);//allows for fixing history problem with improper exit status. 