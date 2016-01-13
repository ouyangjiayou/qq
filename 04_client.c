#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include "/home/ouyang/ouyang/xitonbiancheng/head.h"
#include <pthread.h>
#include <stdlib.h>
 #include <sys/epoll.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

struct head{
           u8  type;
           u8  version;
           u16 length;
};

struct chat{
           char data[1024];
};

struct login{
           char name[64];
           char passwd[128];
};

struct quit{};
struct reg{};
struct file{};

union body{
	struct   login    login;
	struct    quit     quit;
	struct    reg     reg;
	struct     file      file;
	struct      chat    chat;
};

struct  package{
           struct head head;
           union   body  body;
};


void* thread_read(void*argv)
 {
	int sfd = (int)argv;
	int ret;
	 struct package p;
	char buf[1024]={0};
	while(1)
	{           
		 ret =  read(sfd,&p.head,sizeof(p.head));
		 if(p.head.type ==10)
                         {
		ret = read(sfd,buf,p.head.length);
		printf("client:%d\n",sfd);
		//write(1,"client:",6);
		write(1,buf,ret);
	             }else{
	             	perror("unform");
	             }
	}
	return argv;
}

void* thread_write(void*argv)
{
	int sfd = (int)argv;
	int ret;
	char buf[1024]={0};
	char buf1[256] = {0};
	 char buf2[256] = {0};
	 struct package p;
	// p.head.type =10;
	 //p.head.version =1;

	while(1)
	{
		//ret = read(0,buf,1024);
		//buf[ret]=0;
		// printf("buf10=%s\n",buf);
	 //             sscanf(buf ,"%s %s",buf1,buf2);
	 //             printf(" buf1=%s\n",buf1);
	 //             printf("buf11=%s",buf);
	 //             memset(buf,0,1024);
	 //             printf("buf13=%s\n",buf);
                            //  memset(p.head.type, 0, 64);
                           // strcpy(p.head.type, buf1);
                             //memset(buf1, 0, 256);
                           // printf("%s\n",p.head.type);
                        ret =read(0,buf,1024);
		buf[ret] = 0;
		p.head.type = buf[0] - '0';
		p.head.version =1;
		p.head.length =strlen(buf) - 1;
		write(sfd,&p.head,sizeof(p.head));
		write(sfd,&buf[1],p.head.length);
	}
	return argv;
}


int main()
{
	int sfd, ret;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int len;
	char buf[1024]={0};
	pthread_t tid01,tid02;
	void *rret;

	//建立套接字，确定要使用的协议家族
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1){
		perror("socket");
		return -1;
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(8082);
//	sin.sin_addr.s_addr = 
	if(inet_pton(AF_INET,"192.168.1.29",&sin.sin_addr.s_addr) <=0 ){
		perror("inet_pton");
		return -1;
	}

	ret = connect(sfd,(const struct sockaddr*)&sin,(socklen_t)sizeof(sin));
    if(ret == -1){
         perror("connect");
         return -1;
     }

	pthread_create(&tid01,NULL,thread_read,(void*)sfd);
	pthread_create(&tid02,NULL,thread_write,(void*)sfd);
	pthread_join(tid01,&rret);
	pthread_join(tid02,&rret);
	
	close(sfd);
	

}