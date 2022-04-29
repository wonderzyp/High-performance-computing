/**
* @brief 
* 客户端连接至服务端后，以1字节整数形式传递待计算数据
* 每个整型数据占4字节
* 随后传递+, -, /, 计算符，每个占据一字节
* 服务端将计算后结果传回，占领4字节
* ****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
void error_handling(char *message);

int main(int argc, char* argv[]){
  int sock;
  char opmsg[BUF_SIZE];
  int result, opnd_cnt, i;
  struct sockaddr_in serv_adr;

  if (argc!=3){
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock==-1)
    error_handling("sock error\n");
  
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
    error_handling("connect error\n");
  else
    puts("Connected...\n");

  
  // 输入待计算的元素个数
  fputs("Enter the operand count: ", stdout);
  scanf("%d", &opnd_cnt);
  opmsg[0] = (char)opnd_cnt;

  for (int i=0; i<opnd_cnt; ++i){
    printf("Operand %d: ", i+1);
    scanf("%d", (int*)&opmsg[i*OPSZ+1]);
  }

  fgetc(stdin);
  fputs("Operator: ", stdout);
  scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);
  write(sock, opmsg, opnd_cnt*OPSZ+2);

  read(sock, &result, RLT_SIZE);
  printf("The result is: %d\n", result);
  close(sock);
  return 0;
}

void error_handling(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
