# include <sys/shm.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main(int argc, char const *argv[]) {
  /* Connects or creates a shared memory segment large enough to hold a 200 character string.
  Displays the contents of the shared memory. */
  int key;
  int shmid;
  char *data;
  char string[256];
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  printf("Identifer for shared memory segment: %d\n", shmid);
  data = shmat(shmid, (void *)0, 0);
  printf("Pointer attached: %s\n", data);
  /* If the segment was just created, instead show a message saying as much.*/
  if(data) {
    printf("Segment was just created!\n");
  }
  /* Ask the user if they want to change the data in the segment.
  If yes, prompt the user to enter a new string and write that to the segment. */
  printf("Do you want to change the data in the segment? [y/n]\n");
  fgets(string, 200, stdin);
  string[strlen(string)-1] = 0;
  if(strcmp(string, "y") == 0) {
    printf("Enter a new string to the segment: \n");
    fgets(string, 200, stdin);
    string[strlen(string)-1] = 0;
    strcpy(data, string);
    printf("You entered: %s\n", data);
  }
  /*  Ask the user if they want to delete the segment, if yes, then delete it. */
  printf("Do you want to delete the segment? [y/n]\n");
  fgets(string, 200, stdin);
  string[strlen(string)-1] = 0;
  if(strcmp(string, "y") == 0) {
    shmctl(shmid, IPC_RMID, NULL);
    printf("Segment deleted.\n");
  }
  return 0;
}
