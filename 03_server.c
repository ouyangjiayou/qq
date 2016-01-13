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

struct quit{};
struct reg{};
struct file{};

struct chat{
           char data[1024];
};

struct login{
           char name[64];
           char passwd[128];
};

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




typedef void*(*THING)(void* argv);
typedef struct work{
            THING thing;
            void*argv;
            struct work* next;
}QWORK;


typedef struct _node{
              int fd;
            struct _node* next;
}Node;


typedef struct{
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        int max_thread_num;
        pthread_t thread_id[100];
        QWORK* qhead;
        QWORK* qtail;

         Node*  fhead ;
         Node*  ftail;
}TD;


int eh;
struct epoll_event ev,evs[10];

TD td;

// void free()
// {
// 	QWORK* 
// }

void *do_something(void*agrv)
{
		QWORK* pwork = NULL;
		 //QWORK* twork = NULL;
		while(1)
		{
		pwork = NULL;
		pthread_mutex_lock(&td.mutex);
		pthread_cond_wait(&td.cond,&td.mutex);
		
		if(td.qhead){
			pwork = td.qhead;
			if(td.qhead == td.qtail){
				td.qhead = td.qtail=NULL;
			}else{
				td.qhead = td.qhead->next;
			}
		}
		pthread_mutex_unlock(&td.mutex);
		if(pwork)
		{
			pwork->thing(pwork->argv);
                                 free(pwork);
                                 //while()

	              }
		}
	return agrv;
}

void pool_init()
{
	pthread_mutex_init(&td.mutex,NULL);
	pthread_cond_init(&td.cond,NULL);
	td.max_thread_num =100;
	td.qhead = NULL;
	td.qtail = NULL;
	
	td.fhead = NULL;
	td.ftail = NULL;
	int i;
	for(i=0;i<td.max_thread_num;++i)
	{
		pthread_create(&td.thread_id[i],NULL,do_something,NULL);
	}

		// for(i=0;i<td.max_thread_num;i++)
		// {
			
		// 	pthread_detach(td.thread_id[i]);
		// //	printf("%d\n",td.thread_id[i]);
                                       
		// }
}


struct sockaddr_in cin;
//char buf[1024]={0};

void *thread(void*argv)
{
	//struct sockaddr_in tcin;
	int cfd = (int)argv;
	char buf[1024]={0};
	int ret;
	//int len=sizeof(tcin);
              struct package p;
	//getpeername(cfd,(struct sockaddr*)&tcin,(socklen_t*)&len);
               

	   ret = read(cfd,buf,sizeof(buf));
	   if(ret <=0){
	   	close(cfd);
	   	printf("close cfd+%d\n",cfd);
	   	return argv;
	   }
	//   p.head.type = 10;
	   p.head.version = 1;
	   p.head.length = strlen(buf);

                write(cfd,&p.head,sizeof(p.head));
                write(cfd,buf,p.head.length);

	return argv;
}

void pool_add_work(THING thing,void*argv)
{
		QWORK* pwork = malloc(sizeof(sizeof(QWORK)));
		pwork->thing = thing;
		pwork->argv = argv;
		pthread_mutex_lock(&td.mutex);
		if(td.qhead){
			td.qtail->next = pwork;
			td.qtail = pwork;
		}else{
			td.qtail = pwork;
			td.qhead = td.qtail;
		}
		pthread_mutex_unlock(&td.mutex);
		pthread_cond_signal(&td.cond);
}


void parse(int cfd)
{
	char buf[1024];
	int ret;
	int b;
	 struct package p;

	ret = read(cfd, &p.head, sizeof(p.head));
//	memset(p.head.type, 0, 64);
	
	if(ret <=0){
		printf("cfd=%d close!\n",cfd);
		close(cfd);
		ev.data.fd = cfd;
		epoll_ctl(eh,EPOLL_CTL_DEL,ev.data.fd,&ev);
	}

	printf("type =%d\n",p.head.type);
	//memset(p.head.type, 0, 64);
              //    b=p.head.type;                   
 
	// switch(p.head.type)
	// {
	// 	case 1:
	// 		ret = read(cfd,buf,p.head.length);
	// 		if(ret<=0){
	// 			printf("cfd no data!\n");
	// 			return ;
	// 		}
	// 		write(1,&buf,p.head.length);
	// 		write(1,"\n",1);
	// 		break;
	// 	case 2:
	// 		pool_add_work(thread,(void*)cfd);	
	// 		break;

	// 	 case 5:
                                      
                                           ret = read(cfd,buf,sizeof(buf));
			   if(ret <=0){
			   	close(cfd);
			   	printf("close cfd+%d\n",cfd);
			   	//return argv;
			   }
			   p.head.type = 10;
			   p.head.version = 1;
			   p.head.length = strlen(buf);
                                            cfd=b;
		                write(cfd,&p.head,sizeof(p.head));
		                write(cfd,buf,p.head.length);
	// 	               break;

	// 	 case 6:

	//                         //  ret =search(p.head.type);
	// 	                ret = read(cfd,buf,sizeof(buf));
	// 		   if(ret <=0){
	// 		   	close(cfd);
	// 		   	printf("close cfd+%d\n",cfd);
	// 		   	//return argv;
	// 		   }
	// 		   p.head.type = 10;
	// 		   p.head.version = 1;
	// 		   p.head.length = strlen(buf);
 //                                            cfd=6;//p.head.type;
	// 	                write(cfd,&p.head,sizeof(p.head));
	// 	                write(cfd,buf,p.head.length);
	// 	               break;
   

	// 	      default:
	// 		write(1,"unknow data:",strlen("unknow data:"));
	// 		//ret = read(cfd,buf,p.head.length);
	// 		// if(ret<=0){
	// 		// 	printf("cfd no data!\n");
	// 		// 	return ;
	// 		// }
	// 		//write(1,buf,1024);
	// 		write(1,"\n",1);
 //                                       read(cfd,buf,1024);
	// 		break;
	// }

}


// Node* search(int cfd)
// {
              
// }

Node* insert(int cfd)
{
	Node* b = (Node*)malloc(sizeof(Node));
	b->fd = cfd;
	b->next = NULL;
	 if(td.fhead == NULL){
	 	td.fhead=b;
	 }else{
                          b->next = td.fhead;
                         td.fhead = b;
	 }
	 return td.fhead;
}


void show(Node* head)
{
	Node* q = head;
	//getpeername(cfd,(struct sockaddr*)&tcin,(socklen_t*)&len);
	struct sockaddr_in tcin;
	//int cfd = (int)argv;
	char buf[1024]={0};
	int ret;
	int len=sizeof(tcin);

	//printf("client IP=%s, port=%d\n",inet_ntop(AF_INET,&tcin.sin_addr.s_addr,buf,15),ntohs(tcin.sin_port));
	while(q != NULL)
	{
		//printf("%d\n",q->fd);
		getpeername(q->fd,(struct sockaddr*)&tcin,(socklen_t*)&len);
		printf("client%d, IP=%s, port=%d\n",q->fd,inet_ntop(AF_INET,&tcin.sin_addr.s_addr,buf,15),ntohs(tcin.sin_port));
		q = q->next;
	}
}



int main()
{
	int sfd, ret,cfd;
	struct sockaddr_in sin;
	int len;
	char buf[1024]={0};
	int i;
	int eh;
	pthread_t tid;

	pool_init();
             
              eh = epoll_create(8000);
              printf("eh =%d\n",eh);
              if(eh <0)
              {
              	perror("epoll_create");
              	return -1;
              }

	//建立套接字，确定要使用的协议家族
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1){
		perror("socket");
		return -1;
	}

	//绑定地址和端口
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8082);
//	sin.sin_addr.s_addr = 
	if(inet_pton(AF_INET,"192.168.1.29",&sin.sin_addr.s_addr) <=0 ){
		perror("inet_pton");
		return -1;
	}
	ret = bind(sfd,(const struct sockaddr*)&sin,(socklen_t)sizeof(sin));
	if(ret == -1){
		perror("bind");
		return -1;
	}

	//监听
	ret = listen(sfd,30);
	if(ret == -1){
		perror("listen");
		return -1;
	}
	

	int nfound;
	len = sizeof(sin);
	struct epoll_event ev,evs[10];

	ev.data.fd = sfd;
	ev.events = EPOLLIN|EPOLLET;
	
	len = sizeof(cin);
             epoll_ctl(eh,EPOLL_CTL_ADD,sfd,&ev);
            
        //       signal(2,do_sigint);
	while(1)
	{
                 nfound = epoll_wait(eh,evs,10,-1);
               //  printf("nfound = %d\n",nfound);
                 //sleep(1);
                 if(nfound < 0){
                 	perror("epoll_wait");
                 	continue;
                 }else if(nfound ==0){
                 	printf("time out\n");
                 	continue;
                 }else{

                 	for(i=0; i<nfound;++i)
                 	{
                 		if(evs[i].data.fd == sfd){
                 			cfd = accept(sfd,(struct sockaddr*)&cin,(socklen_t*)&len);
                 		        //     printf("cfd=%d\n",cfd);
                 		              if(cfd == -1){
                 		              	perror("accept");
                 		              	continue;
                 		              }else {
                 		              	ev.data.fd = cfd;
                 		              	ev.events = EPOLLIN|EPOLLET;
                 		              	epoll_ctl(eh,EPOLL_CTL_ADD,cfd,&ev);
                                                                   
                                                                td.fhead = insert(cfd);
                                                                show(td.fhead);
                                                                  //Node* b = (Node*)malloc(sizeof(Node));
                                                                  //if()

                 		              	continue;}
                 		              
                 		}else  if(evs[i].events == EPOLLIN | EPOLLET)
                 		                {

                 			parse(evs[i].data.fd);
					}
			}		
                 	}
                 }
	  	
	close(sfd);
	close(cfd);
}



