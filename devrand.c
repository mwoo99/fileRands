#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

//get rand int using 4 bytes
int randInt() {
  int randStuff = open("/dev/random",O_RDONLY);
  //printf("%d : %s\n", errno, strerror(errno));
  int ans;
  if (read(randStuff,&ans,4) == -1)
    printf("errno: %d \nerror: %s", errno, strerror(errno));
  close(randStuff);
  return ans;
  }

int main() {
  int i;
  umask(0);
  //populate array
  printf("Generating random numbers:\n");
  int arr[10];
  for(i=0; i<10; i++){
    arr[i] = randInt();
    printf("\tarr[%d]: %d\n",i,arr[i]);
  }

  //write the array to a file
  printf("\nWriting numbers to file...\n");
  int file = open("randFile.txt",O_CREAT | O_RDWR,0666);
  write(file,arr, 10 * sizeof(int));
  close(file);

  //reading
  printf("\nReading numbers from file...\n");
  int fileArr[10];
  file = open("randFile.txt",O_RDONLY);
  read(file,fileArr, 10* sizeof(int));

  //verifying
  printf("\nVerification that written values were the same:\n");
  for(i = 0; i<10; i++)
    printf("\tfileArr[%d]: %d\n",i,fileArr[i]);
  close(file);
  return 0;
}
