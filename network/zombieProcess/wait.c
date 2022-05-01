/**
* @brief wait函数销毁子进程，同时可获得子进程的返回值
* 调用wait时，若没有已经终止的子进程，将阻塞直到有子进程终止
* ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
  int status;
  pid_t pid = fork();
  
  if (pid==0){
    return 3;
  } else { 
    // 子进程执行区域
    printf("child pid: %d\n", pid);
    pid = fork();
    if (pid==0){
      sleep(3); // 子进程延迟返回，父进程会阻塞
      exit(7);
    } else {
      printf("child pid: %d\n", pid);
      wait(&status);
      if (WIFEXITED(status))
        printf("Child send one: %d\n", WEXITSTATUS(status));
      wait(&status);
      if (WIFEXITED(status))
        printf("Child send two: %d \n", WEXITSTATUS(status));
        sleep(5);
    }
  }
  return 0;
}