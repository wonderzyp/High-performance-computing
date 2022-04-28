#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char* argv[]){

  if (argc!=3){
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(1);
  }

  char message[BUF_SIZE];
  int sock;
  struct sockaddr_in serv_addr;
  size_t str_len;


  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    error_handling("sock error\n");
  
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
    error_handling("connect error\n");
  else
    puts("Connected...\n");
  
  while (1)
  {
    fputs("press Q to quit\n", stdout);
    fgets(message, BUF_SIZE, stdin); // 输入待传输的信息

    if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
      break;

    write(sock, message, strlen(message)); // TCP不存在数据边界，服务端可能在尚未完全收到信息调用read
    str_len = read(sock, message, strlen(message));
    message[str_len] = 0;
    printf("Message from server: %s\n", message);
  }
  close(sock);
  return 0;
}


void error_handling(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
