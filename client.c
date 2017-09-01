#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
 
 
#define MAX_LINE 102400
 
int main(int argc,char **argv)
{
    struct sockaddr_in sin;     //服务器的地址
    char buf[MAX_LINE];
    int sfd;
    int port = 80;
    char *str = "HTTP/1.1 200 OK\r\nContent-Length:190\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
    char *serverIP = "180.149.134.141";
    if(argc > 1)
    {
        str = argv[1];  //读取用户输入的字符串
    }
    bzero((void *)&sin,sizeof(sin));
    sin.sin_family = AF_INET;   //使用IPV4地址族
     
    inet_pton(AF_INET,serverIP,(void *)&(sin.sin_addr));
    sin.sin_port = htons(port);
     
    sfd = socket(AF_INET,SOCK_STREAM,0);
     
    connect(sfd,(struct sockaddr *)&(sin),sizeof(sin));
 
    printf("str = %s\n" , str);
    write(sfd , "GET / HTTP/1.1\r\nContent-Type: text/html; charset=UTF-8\r\nAccept-Encoding:gzip, deflate, sdch\t\nHost:WeiBo.comn\r\nUser-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.221 Safari/537.36 SE 2.X MetaSr 1.0\r\n\r\n" , strlen(str)+1);
    read(sfd , buf , MAX_LINE);
    printf("recive from server: %s\n" , buf);
 
    close(sfd);
     
    return 0;
}
