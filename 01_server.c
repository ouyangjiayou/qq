#include "/home/ouyang/ouyang/xitonbiancheng/head.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

struct head{
           u8  type[64];
           u8  version;
           u16 length;
};

typedef void*(*THING)(void* argv);
typedef struct work{
            THING thing;
            void*argv;
            struct work* next;
}QWORK;


typedef struct _node{
              int fcd;
              char name[64];
              char passowed[64];
            struct _node* next;
}Node;


struct  package{
           struct head head;
        //   union   body  body;
};

typedef struct{
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        int max_thread_num;
        pthread_t thread_id[100];
        QWORK* qhead;
        QWORK* qtail;

         Node*  fhead ;
         Node*  ftail;

         Node* thead;
         Node* ttail;
}TD;


int eh;
struct epoll_event ev,evs[10];

TD td;

void *do_something(void*agrv)
{
		QWORK* pwork = NULL;
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

	 td.thead = NULL;
              td.ttail= NULL;
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


void show(Node* head)
{
	Node* q = head;
	while(q != NULL)
	{
		 printf("%s %s %d\n",q->name,q->passowed,q->fcd);
		q = q->next;
	}
}

void free_list(Node* head)
{
          Node* q = NULL;
          while(head != NULL)
          {
                     q = head;
                      head= head->next;
                      free(q);      
          }
}

Node* insert_b(Node p)
{
	Node* b = (Node*)malloc(sizeof(Node));
	//b->fd = cfd;
	strcpy(b->name,p.name);
	strcpy(b->passowed,p.passowed);
	b->fcd=p.fcd;
	b->next = NULL;
	 td.ttail = td.thead;
	 if(td.thead == NULL){
	 	td.thead=b;
	 	 td.ttail = b;
	 	  td.ttail ->next =NULL;
	 	  return  td.thead ;
	 }
	 	while(td.ttail->next != NULL)
	 	{
	 		td.ttail = td.ttail->next;
	 	}
               td.ttail->next = b;
	 
	 return  td.thead ;
}


Node* insert(Node p)
{
	Node* b = (Node*)malloc(sizeof(Node));
	strcpy(b->name,p.name);
	strcpy(b->passowed,p.passowed);
	//b->fcd=p.fcd;
	b->next = NULL;
	 td.ftail = td.fhead;
	 if(td.fhead == NULL){
	 	td.fhead=b;
	 	 td.ftail = b;
	 	  td.ftail ->next =NULL;
	 	  return td.fhead;
	 }
	 	while(td.ftail->next != NULL)
	 	{
	 		td.ftail = td.ftail->next;
	 	}
               td.ftail->next = b;
	 
	 return td.fhead;
}



void load()
{
       Node* d  = NULL;
       FILE* fd;
       char buf[64];
       int ret;
       Node h;
       fd = fopen("a.txt","r+");
       while(1)
            {
                       ret =fscanf(fd,"%s %s\n",h.name,h.passowed);   
                        if(ret<=0)break;
                          td.fhead = insert(h);                  
            }
            fclose(fd);

}

Node* search_b(char* name)
  {          
  	 printf("%s\n",name);
  	 Node* y = td.thead;
  	 while(y != NULL)
  	 {
  	 	if(strcmp(y->name,name) == 0)
  	 	{
  	 		return  y;
  	 	}
  	 	y=y->next;
  	 }

  	 return NULL;

  }

  Node* search(char* name)
  {          
  	 printf("%s\n",name);
  	 Node* y = td.fhead;
  	 while(y != NULL)
  	 {
  	 	if(strcmp(y->name,name) == 0)
  	 	{
  	 		return  y;
  	 	}
  	 	y=y->next;
  	 }

  	 return NULL;

  }

  Node* search_cfd(int cfd)
  {
  	 Node* j = td.thead;
  	 while(j != NULL)
  	 {
  	 	if( j->fcd == cfd)
  	 	{
  	 	 	return  j;
  	 	}
  	 	j=j->next;
  	 }

  	 return NULL;

  }


void removelist(int cfd)
{
            Node* g= td.thead;
            Node* t = td.thead;
            //printf("cfd=%d\n",cfd);
         //  Node* p = search_cfd(fcd);
             if(g->fcd == cfd){
             	         td.thead = td.thead->next;
             	         free(g);
             	         return;
             }
             while(g->next !=NULL){
             	      if(g->next->fcd == cfd){
             	      	t=g->next;
             	      	g->next=t->next;
             	      	free(t);
             	      	return;
             	      }
             	      g=g->next;
             }

           //  while(g != NULL)
           //  { 
           //             if(g->fcd == cfd)
           //             {
           //             	   break;
           //             }
           //         t = g; 
           //         g=g->next;
           //  }
          
           //  printf("cfd=%s\n",g->name);
           //  if(g == td.thead)
           //  {
           //  	        td.thead = td.thead->next;
           //            free(g);
           //   //     }
           //            return ;
           //  }else if(g == NULL){
           //             free(t);
           //             return;
           //  }
           //           t->next = g->next;
           //  	        free(g);
            
           // return ;

}

  void save(Node* head)
{           
	FILE* fd;
	 fd = fopen("b.txt","w+");
	 Node* z = NULL;
	 char buf[1024] ={0};
	z = head;
	 while(z != NULL)
	 {           
	 	fprintf(fd,"%s %s %d\n",z->name,z->passowed,z->fcd);  
	 	z =z->next;
	 }
	 fclose(fd);

}



struct sockaddr_in cin;
//char buf[1024]={0};


void*regiser(void*argv)
{
	int cfd = (int)argv;
	char buf[1024] ={0};
	char buf1[1024]={0};
	char buf2[1024]={0};
	int ret;
	FILE* fd = fopen("a.txt","a");
	// while(1)
	// {
                    ret = read(cfd,buf,sizeof(buf));
                    //printf("buf=%s\n",buf);
                       strcpy(buf1,buf);
                       printf("buf1=%s\n",buf1);
                       memset(buf,0,1024);

                    ret = read(cfd,buf,sizeof(buf));
                       strcpy(buf2,buf);
                       printf("buf2=%s\n",buf2);
                    //   memset(buf,0,1024);
                       if(ret <=0){
	   	close(cfd);
	   	printf("close cfd+%d\n",cfd);
	   	return argv;
	                }
                            fprintf(fd,"%s %s\n",buf1,buf2);
                            write(cfd,"注册成功",12);
	fclose(fd);
}

void *thread(void*argv)
{
	//struct sockaddr_in tcin;
	int cfd = (int)argv;
	char buf[1024]={0};
	int ret;
	Node* k=NULL;
	Node m;
              struct package p;
              while(1)	   
	   {
	   	ret = read(cfd,buf,sizeof(buf));
	   if(ret <=0){
	   	close(cfd);
	   	printf("close cfd+%d\n",cfd);
	   	return argv;
	                }

	                load();

	               k   = search(buf);
	              if(k != NULL)
	                     { 
	                     	//  p.head.version = 0;
	                     	  //write(cfd,&p.head,sizeof(p.head));
	                     	//write(cfd,"nook",4);
	                     	write(cfd,"ook",4);
	                     	
	                     	loop:
	                       read(cfd,buf,sizeof(buf));
	                       printf("bufook=%s\n",buf);
                                       
                                         if(strcmp(k->passowed,buf) == 0){
                                         	 //free(td.fhead);
                                         	printf("nihao\n");
                                         	k->fcd = cfd;
                                         	 m.fcd  = k->fcd;
                                         	strcpy( m.name , k->name);
                                         	 strcpy(m.passowed ,k->passowed);
                                                                
                                                        
                                         	   p.head.version = 1;
			   //p.head.length = strlen(buf);
                                            //cfd = t->fcd;
                                             //printf("t->fcd=%d\n",t->fcd);
		                write(cfd,&p.head,sizeof(p.head));
                                         	//write(cfd,"oook",4);

                                         	insert_b(m);

                                                   printf("---------------------\n");
                                         	 show(td.thead);
                                         	save(td.thead);
                                         	//free_list(td.fhead);
                                        	break;//}
                                   
                                         }else{
                                         	printf("ni bushi henbang\n");
                                         	 p.head.version = 2;
			   // //p.head.length = strlen(buf);
      //                                       //cfd = t->fcd;
      //                                        //printf("t->fcd=%d\n",t->fcd);
		                write(cfd,&p.head,sizeof(p.head));

                                         	write(cfd,"nok",3);
                                         	goto loop;
    //                                      	if(td.thead == NULL)
				// {
				// 	printf("empty\n");
				// }else{
				// removelist(cfd);
				// }
                                         }
	                     }else{

	                     //	printf("kkkkk\n");
	                      	  p.head.version = 3;
			   // //p.head.length = strlen(buf);
      //                                       //cfd = t->fcd;
      //                                        //printf("t->fcd=%d\n",t->fcd);
		                write(cfd,&p.head,sizeof(p.head));
	                     	write(cfd,"nook",4);
    //                                      	if(td.thead == NULL)
				// {
				// 	printf("empty\n");
				// }else{
				// removelist(cfd);
				// }
	                     	// write(cfd,"no user",7);
	                     }
                //   show(td.fhead);
	}
	return argv;
}



void* show_list(void*argv)
{
	int cfd = (int)argv;
	char buf[1024]={0};
               Node g;
               Node* k= td.thead;
                 struct package p;
                                         //    strcpy(p.head.type , s->name);
	                              //     printf("p.head.type=%s\n",p.head.type);
			   p.head.version = 6;
	write(cfd,&p.head,sizeof(p.head));
			   //p.head.length = strlen(buf);
               while(k != NULL)
               {
                        g.fcd = k->fcd;
                        strcpy(g.name,k->name);
                        strcpy(g.passowed,k->passowed);
                        write(cfd,&g,sizeof(g));
                      //  printf("listooooooo\n");
                        k= k->next;
                        if(k == NULL){
                        	g.fcd=0;
                        	write(cfd,&g,sizeof(g));
                        }
               }
      return argv;
}


void* alltalk(void*argv)
{
       int cfd = (int)argv;
       char buf[1024]={0};
       int ret;

       Node* k;//=td.thead;
        Node* s= NULL;
        struct package p;

          while(1)
           //  b:
        	{
             a:
              
        	ret = read(cfd, &p.head, sizeof(p.head));
        
          ret = read(cfd,buf,sizeof(buf));
          
             printf("qunliao buf=%s\n",buf);
	   if(ret <0){
	   	
	             
	             if(td.thead == NULL)
	   	{
	   		printf("empty\n");
                                          break;
	   		//exit(0);
	   	}else{
	   		removelist(cfd);
	   	}
             
	   	close(cfd);
	   	printf("close cfd+%d\n",cfd);
	
	           //    goto b;
	   	// if(td.thead == NULL)
	   	// {
	   	// 	printf("empty\n");
	   	// }else{
	   	// 	removelist(cfd);
	   	// }
	   	//return argv;
	   }
                
          
	   s = search_cfd(cfd);   
                 if(s==NULL)
                 {
                         goto a;   
                 }
	  strcpy(p.head.type , s->name);
	
	                           printf("p.head.type=%s\n",p.head.type);
	   p.head.version = 1;
	
	   p.head.length = strlen(buf);
            
	         k=td.thead;
	     while(k != NULL)
	            {

	            	write(k->fcd,&p.head,sizeof(p.head));
	            write(k->fcd,buf,p.head.length);
	            printf("1234566=%s\n",buf);
	         
	            k=k->next;
                            }
             
                               memset(buf,0,1024);
                 }
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
	char buf1[64];
	int ret;
	int b;
	Node* t;
	Node* s;
	 struct package p;
	// a:
	 printf("ffsdfsdfsdfdf\n");

	ret = read(cfd, &p.head, sizeof(p.head));
	if(ret <=0){
		printf("cfd=%d close!\n",cfd);
		if(td.thead == NULL)
		{
			printf("empty\n");
		}else{
		removelist(cfd);
		}
		close(cfd);
		ev.data.fd = cfd;
		epoll_ctl(eh,EPOLL_CTL_DEL,ev.data.fd,&ev);

	}
              strcpy(buf1,p.head.type);
            
              printf("buf1=%s\n",buf1);

              if(buf1[0] == 'g')
              {
              	pool_add_work(thread,(void*)cfd);
              }else if(buf1[0] == 'f'){
                            // printf("sddsddsd\n");
                          pool_add_work(regiser,(void*)cfd);   
              }else if(buf1[0] == 'h' ||buf[0]=='h'){
              	//printf("oooooooooooooook\n");
                            pool_add_work(show_list,(void*)cfd);
              }else if(buf1[0] == 'q'){
                            pool_add_work(alltalk,(void*)cfd);
              }else{
              	
              	  t = search_b(buf1);
              
              	   if(t != NULL)
              	   {       
              	   	  ret = read(cfd,buf,sizeof(buf));
              	                
              	             //    printf("buf=%s\n",buf);
			   if(ret <=0){
			   	close(cfd);
			   	printf("close cfd+%d\n",cfd);
			   	//return argv;
			   }
                                              s = search_cfd(cfd);
			  strcpy(p.head.type , s->name);
	                               //    printf("p.head.type=%s\n",p.head.type);
			   p.head.version = 1;
			   p.head.length = strlen(buf);
                                            //cfd = t->fcd;
                                          //   printf("t->fcd=%d\n",t->fcd);
		                write(t->fcd,&p.head,sizeof(p.head));
		                write(t->fcd,buf,p.head.length);
		                memset(buf,0,1024);
              	   }
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


	int keep_alive =1;
	int keep_idle =5;
	int keep_interval = 5;
	int keep_count = 3;
             

             // signal(SIGALRM,signal_alarm);
               
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
             setsockopt(cfd,SOL_SOCKET,SO_KEEPALIVE,(void*)&keep_alive,sizeof(int));
              setsockopt(cfd,SOL_TCP,TCP_KEEPIDLE,(void*)&keep_idle,sizeof(int));
              setsockopt(cfd,SOL_TCP,TCP_KEEPINTVL,(void*)&keep_interval,sizeof(int));
              setsockopt(cfd,SOL_TCP,TCP_KEEPCNT,(void*)&keep_count,sizeof(int));
                 		              	continue;}
                 		              
                 		}else  if(evs[i].events == EPOLLIN | EPOLLET)
                 		                {
    //              		                	memset(buf, 0, 1024);
				// read(evlist[i].data.fd, buf, 1024);
				// if(buf[0] == 'g')

				//printf("recieve : %s\n", buf);
                 			parse(evs[i].data.fd);
					}
			}		
                 	}
                 }
	  	
	close(sfd);
	close(cfd);
}



