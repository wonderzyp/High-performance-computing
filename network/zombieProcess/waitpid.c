#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
  int status;
  pid_t pid = fork();
  

  if (pid == 0){
    sleep(9);
    return 24;
  } else{
    
    // 有点像自旋锁，不断询问是否返回
    while(!waitpid(-1, &status, WNOHANG)){ // WNOHANG子进程未返回时，返回0
      sleep(3);
      puts("Sleep 3s\n");
    }

    if (WIFEXITED(status))
      printf("Child send %d\n", WEXITSTATUS(status));
  }
  return 0;
}