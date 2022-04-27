#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);


int main(int argc, char *argv[]){
  int serv_sock;
  int clnt_sock;

  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size;

  char message[] = "hello world";

  if (argc!=2){
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  // 初始化socket: TCP协议
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock==-1)
    error_handling("socket error()\n");
  
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 服务器端可设置自动获取IP地址(单NIC)
  serv_addr.sin_port = htons(atoi(argv[1]));

  // 将serv_addr结构体信息绑定至socket
  if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
    error_handling("bind() error\n");
  
  // 监听
  if (listen(serv_sock, 5)==-1)
    error_handling("listen() error\n");
  
  clnt_addr_size = sizeof(clnt_addr);
  // accept返回新的socket对，实现连接通信
  clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

  write(clnt_sock, message, sizeof(message));
  close(clnt_sock);
  close(serv_sock);
  return 0;
}

void error_handling(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
