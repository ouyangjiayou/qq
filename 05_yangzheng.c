#include <stdio.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

// typedef struct _data{
              

// };



typedef struct _node{
              int fd;
              char name[64];
               char passowed[64];
            struct _node* next;
}Node;

Node* head=NULL;
Node*tail=NULL;
int c=0;

Node* insert(Node* head, Node p)
{
	 // printf("%s\n",p->name);
  //                               printf("%s\n",p->passowed);
	Node* b = (Node*)malloc(sizeof(Node));
	strcpy(b->name,p.name);
	strcpy(b->passowed,p.passowed);
	b->fd=p.fd;
	//b = p;
	b->next = NULL;
	// printf("%s  %s\n",b->name,b->passowed);
                         //       printf("%s\n",b->passowed);
	 // printf("head=%s\n",head->fd);
	 tail = head;
	 if( head == NULL){
	 	head=b;
	 	tail = b;
	 	printf("OOOK\n");
	 	tail->next=NULL;
	 	return head;
	 }
	else{
	 	// while(tail->next != NULL)
	 	// {
	 	// 	tail = tail->next;
	 	// 	//printf("%s\n",tail->name );
	 	// 	printf("oooo\n");
	 	// }
                          b->next = head;
                         head = b;
	 	//sleep(1);
	 	 // printf("c=%d",c++);
	   //     tail->next=b;
	  //printf("head=%s\n",head->fd);

	 }
	 return head;
}

void show(Node* head)
{

	Node* q= head;
    while( q !=NULL)
                        {
                        	  sleep(1);
                        	  printf("%s %s %d\n",q->name,q->passowed,q->fd);
                        	  q= q->next;
                        }
}


int main()
{          
	 FILE* fd;
	 int ret;
	 Node* head;
	 Node d;

	 char buf[64];
	 char buf1[32];
	 char buf2[32];
	 char buf3[32];
                                                

	  fd = fopen("b.txt","r+");
       // while(1)
       //     {   
	  Node* p = NULL;
	  head=NULL;
                      //ret =read(fd,buf,3);
            	     while(1)
                     // sprintf(buf,"%s%s%s",buf1,buf2,buf3);
                       //buf[ret]=0;
                      //  if(ret<=0)break;
                        {
                             ret =fscanf(fd,"%s %s %d",d.name,d.passowed,&d.fd);   
                               if(ret<=0)break;
                               sleep(1);
                            head = insert(head,d);
                                // p = (Node*)malloc(sizeof(Node));
                                // p->next = NULL;
                                // p->fd = d.fd;
                                // p->name[64] = d.name;
                                 
                                // printf("%s\n",p->name);
                                // printf("%s\n",p->passowed);

                                // p->name[64]=d.name;
                                // p->passowed[64]=d.passowed;
                               // if(head == NULL)
                               // { 
                               // 	head=p;
                               // 	head->next=NULL;

                               // }else{
                               // 	p->next=head;
                               // 	head = p;
                               // 	                }
                        	//printf("%s\n",buf);

                        }
                       show(head);
                  
                  printf("ooook\n");
                  close(fd);
                   // p=head;
                    
            // // }
}