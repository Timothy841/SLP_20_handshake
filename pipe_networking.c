#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;
  char line[100];
  int piper = open("mario", O_RDONLY);
  if (piper == -1){
	mkfifo("mario", 0644);
	piper = open("mario", O_RDONLY);
  }
  read(piper, line, 100);
  sscanf(line, "%s\n", line);
  printf("Message \"%s\" received.\n", line);
  //remove("mario");
  printf("[%s]\n", line);
  int pipew = open(line, O_WRONLY);
  if (pipew == -1){
  	mkfifo(line, 0644);
  	pipew = open(line, O_WRONLY);
  }
  strcat(line, "1");
  write(pipew, line, 100);
  printf("Wrote message to secret pipe.\n");
  //remove(line);
  read(piper, line, 100);
  sscanf(line, "%s\n", line);
  printf("Message \"%s\" received.\n", line);
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;
  char line[100] = "luigi";
  int pipew = open("mario", O_WRONLY);
  if (pipew == -1){
	mkfifo("mario", 0644);
	pipew = open("mario", O_WRONLY);
  }
  write(pipew, line, 100);
  printf("Wrote message to well-known pipe.\n");
  //remove("mario");
  int piper = ("luigi", O_RDONLY);
  if (piper == -1){
	mkfifo("luigi", 0644);
	piper = open("luigi", O_RDONLY);
  }
  read(piper, line, 100);
  sscanf(line, "%s\n", line);
  printf("Message \"%s\" received.\n", line);
  //remove("luigi");
  strcat(line, "2");
  write(pipew, line, 100);
  printf("Wrote message to well-known pipe.\n");
  return from_server;
}
