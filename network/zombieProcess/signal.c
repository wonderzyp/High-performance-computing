#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
  if (sig == SIGALRM)
    puts("Time out!");
  alarm(2);
}


void keyControl(int sig){
  if (sig == SIGINT)
    puts("CTRL+C pressed");
}

int main(int argc, char* argv[]){
  int i;
  signal(SIGALRM, timeout);
  signal(SIGINT, keyControl);
  alarm(2);

  for (i=0; i<3; ++i){
    puts("wait...");
    sleep(2);
  }
  return 0;
}