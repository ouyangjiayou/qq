#include "/home/ouyang/ouyang/xitonbiancheng/head.h"
const char*default_ip ="127.0.0.1";

int main(int argc,char*argv[])
{
	int sfd,ret;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int len;
	char buf[1024]={0};

	if(argc<2){
		printf("use dafault ip:%s\n",default_ip);
	}else{
		default_ip = argv[1];
		printf("current ip:%s\n",default_ip);
	}
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}
	sin.sin_family =AF_INET;
	sin.sin_port = htons(8081);
	if(inet_pton(AF_INET,default_ip,&sin.sin_addr.s_addr) <=0 ){
		perror("inet_pton");
		return -1;
	}
              
              while(1)
              {
              	len=sizeof(sin);
              	ret =read(0,buf,1024);
              	buf[ret]=0;
              	sendto(sfd,buf,strlen(buf),0,(struct sockaddr*)&sin,len);
              }
  close(sfd);
}