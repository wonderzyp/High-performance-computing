#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
  if (sig == SIGALRM)
    puts("Time out!");
  alarm(2);
}

int main(int argc, char* argv[]){
  int i;
  struct sigaction act;
  
}