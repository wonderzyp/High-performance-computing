#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4

void error_handling(char *message);

int calculate(int opnum, int opnds[], char op){
  int result=opnds[0], i;
  switch (op)
  {
  case '+':
    for (int i=1; i<opnum; ++i) result+=opnds[i];
      break;
  case '-':
    for (int j=1; j<opnum; ++j) result -= opnds[i];
    break;
  case '*':
    for (int j=1; j<opnum; ++j) result *= opnds[i];
    break;
  default:
    break;
  }
  return result;
}


int main(int argc, char* argv[]){

  int serv_sock, clnt_sock;
  int opnd_cnt;
  char opinfo[BUF_SIZE];

  if (argc!=2){
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock==-1)
    error_handling("socket error\n");
  
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
    error_handling("bind error\n");
  
  if (listen(serv_sock, 5)==-1)
    error_handling("listen error\n");
  
  clnt_addr_size = sizeof(clnt_addr);

  clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
  if (clnt_sock ==-1)
    error_handling("accept error\n");
  else
    printf("Connected client successfully\n");
  
  
  opnd_cnt = 0;
  read(clnt_sock, &opnd_cnt, 1);
  int recv_len = 0;
  int recv_cnt = 0;

// 保证完整收到传输数据
  while((opnd_cnt*OPSZ+1)>recv_len){
    recv_cnt = read(clnt_sock, &opinfo[recv_len], OPSZ);
    recv_len += recv_cnt;
  }

  int result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
  write(clnt_sock, (char*)&result, sizeof(result));
  close(clnt_sock);
  return 0;
}

void error_handling(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
