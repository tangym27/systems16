#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

int main(){
  key_t key;
  int shmid;
  char * data;

  // Connects or creates a shared memory segment large enough to hold a 200 character string.
  // how to get a pointer to a shared memory segment:
  key = ftok("somefile", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, 0);

  //Displays the contents of the shared memory.
  if (*data){
    printf("Contents of the shared memory: %s\n", data);
  }
  else{
    printf("Segment was just created. It is empty (like my soul). \n");
  }

  char cmd[200];

  printf("Would you like to change the data in the segment?: (y/n)");
  fflush(stdout);
  fgets(cmd, 200, stdin);

if (cmd[0] == 'y'){
    printf("\n");
    printf("Please enter a new string: ");
    fflush(stdout);
    fgets(cmd, 200, stdin);
    strcpy(data, cmd);
  }

  cmd[0] = '\0';


    printf("\n");
    printf("Do you want to delete the segment?: (y/n) ");
    fflush(stdout);
    fgets(cmd, 200, stdin);

  if (cmd[0] == 'y'){
    printf("\n");
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("The segment is deleted.\n");
  }
  else{
    printf("The segment is not deleted.\n");
  }

}
