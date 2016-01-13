#include "/home/ouyang/ouyang/xitonbiancheng/head.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

struct head{
           u8  type[64];
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

struct  package{
           struct head head;
  //         union   body  body;
};

typedef struct _node{
              int fcd;
              char name[64];
              char passowed[64];
            struct _node* next;
}Node;




void thread(int sfd)
{
	//  int sfd = (int)argv;
	int ret;
	char buf[1024]={0};
	Node g;
	while(1)
	{
		//printf("nice=\n");
		ret = read(sfd,&g,sizeof(g));
		if(g.fcd == 0)break;
		printf("%s  %s  %d\n",g.name,g.passowed,g.fcd);
		//sleep(1);
	}

       // pthread_exit(NULL);
       // return argv;
}


void* thread_read(void*argv)
 {
	int sfd = (int)argv;
	int ret;
	 struct package p;
	char buf[1024]={0};
	while(1)
	{           
		 ret =  read(sfd,&p.head,sizeof(p.head));
		// if(p.head.type ==10)
                         //{
		// printf("p.head=%s\n",p.head.type);
		 if(p.head.version == 6)
		 {
                                        thread(sfd);
		 }else{

		write(1,p.head.type,sizeof(p.head.type));
		ret = read(sfd,buf,p.head.length);
		//printf("buf=%s\n",buf);
		write(1,"  : ",5);
		//write(1,"client:",6);
		write(1,buf,ret);
		 write(1,"\n",1);
		 memset(buf,0,1024);
		 memset(p.head.type,0,64);
	            // }else{
	             //	perror("unform");
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
	 char buf3[256]={0};
	 struct package p;
	// p.head.type =10;
	 //p.head.version =1;

	while(1)
	{
		ret = read(0,buf,1024);
		buf[ret]=0;
	             sscanf(buf ,"%s %s",buf1,buf2);
	            
	             // printf("buf2=%s\n",buf2);
	              
	             memset(buf,0,1024);
	          
                            memset(p.head.type, 0, 64);
                               if(strcmp(buf2,"")==0)
                               {
                                     //printf("buf3=%s\n",buf3);
                                  strcpy(p.head.type,buf3);
                                    p.head.version = 1;
                          p.head.length = strlen(buf1);
                     
		 write(sfd,&p.head,sizeof(p.head));
		 memset(p.head.type, 0, 64);
		 write(sfd,&buf1,p.head.length);
		 memset(buf1, 0, 256);
		 memset(buf,0,1024);
                                   
                               }else{

                            strcpy(p.head.type, buf1);
                             strcpy(buf3,buf1);
                            
                             memset(buf1, 0, 256);
                        
                           p.head.version = 1;
                          p.head.length = strlen(buf2);
                     
		 write(sfd,&p.head,sizeof(p.head));
		 memset(p.head.type, 0, 64);
		 write(sfd,&buf2,p.head.length);
		 memset(buf2, 0, 256);
		 memset(buf,0,1024);
		}
		  
	}
	return argv;
}

// void* thread(void*argv)
// {
//          int sfd = (int)argv;
// 	int ret;
// 	char buf[1024]={0};
// 	Node g;
// 	while(1)
// 	{
// 		printf("nice=\n");
// 		ret = read(sfd,&g,sizeof(g));
// 		if(ret<0)break;
// 		printf("%s  %s  %d\n",g.name,g.passowed,g.fcd);
// 		//sleep(1);
// 	}

//        pthread_exit(NULL);
//        return argv;
// }




int main()
{
	int sfd, ret;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int len;
	char buf[1024]={0};
	char buf1[4]={0};
	//char buf2[4]={0};
	pthread_t tid01,tid02,tid03;
	void *rret;

	char s1[] = "f";
                    char s2[] = "g";
                    char s3[] = "k";
                  // char s4[] = "4";
                    char s4[5] = {0} ;
                    char s5[]="h";

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
     }else{
                    
                    printf("--------------------------------------------------------------------------------\n");
                    printf("                          f.注册                                                            \n");
                    printf("                          g.登陆                                                            \n");
                    printf("                          k.退出                                                            \n");
                    printf("--------------------------------------------------------------------------------\n");
                    printf("please choice one ! \n");

                    scanf("%s",s4);  
                    if(strcmp(s4,s1) == 0)
                    {
                            buf1[0] = 'f';
                    write(sfd,buf1,1);
     	       printf("enter name:\n");
     	       ret = read(0,buf,6);
                    write(sfd,buf,3);
                    printf("enter passwd:\n");
                    ret = read(0,buf,6);
                    write(sfd,buf,3);
                    read(sfd,buf,sizeof(buf));
                    printf("%s\n",buf);
                    }
                    else if(strcmp(s4,s2) == 0)
                    {
                    	buf1[0]='g';
                    write(sfd,buf1,1);
                    //getchar();
     	       printf("enter name:\n");
     	       ret = read(0,buf,6);
                    write(sfd,buf,3);
                    printf("enter passwd:\n");
                    ret = read(0,buf,6);
                    write(sfd,buf,3);


                    read(sfd,buf,sizeof(buf));
                    printf("%s\n",buf);
                    printf("--------------------------------------------------------------------------------\n");
                    printf("                          h.显示在线人数                                           \n");
                    //printf("                          2.登陆                                                            \n");
                    printf("                          k.退出                                                            \n");
                    printf("--------------------------------------------------------------------------------\n");
                    printf("please choice one ! \n");
                     scanf("%s",s4); 
                     if(strcmp(s4,s5) == 0)
                     {
                     	buf1[0]='h';
                     	write(sfd,buf1,1);
                         //  pthread_create(&tid03,NULL,thread,(void*)sfd);
                           //pthread_cancel(tid03);
                         //   thread(sfd);
                           // sleep(1);
                         //  pthread_detach(tid03);
                     }else{
                                 exit(0);
                         }

                    }else if(strcmp(s4,s3) == 0)
                    {
                           exit(0);
                    }

     }
             printf("talk begin\n");
	pthread_create(&tid01,NULL,thread_read,(void*)sfd);
	pthread_create(&tid02,NULL,thread_write,(void*)sfd);
	pthread_join(tid01,&rret);
	pthread_join(tid02,&rret);
	
	close(sfd);
	

}