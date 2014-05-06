#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>
#include<sys/stat.h>
#include<sys/param.h>
#include<time.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

/*--------------------------------------------------*/
/*init_deamon function will set up a deamon process;*/
/*The deamon process will running background ;      */
/*Coping jobs background without the shell or bash; */
/*--------------------------------------------------*/

void init_deamon(void){
    int pid;
    int i;
    /*Father exit & hand out the children process to init*/
    if(pid=fork()){
        exit(0);
        }
    else if(pid<0){
    /*THIS PLACE SHOULD INSERT LOG HANDLER*/
    /*The fork() is erro & need be reported*/
        exit(1);
        }
    /*This must be the first Children process, running background*/
    /*Creat a new session here by using setsid()*/
    /*First Children process become the captail of session*/
    setsid();
    /*The second children here,second children could not be Capital of the Group*/
    if(pid=fork())
            exit(0);
    else if(pid<0)
    /*THIS PLACE SHOULD INSERT LOG HANDLER*/
    /*The fork() is erro & need be reported*/
            exit(1);
    /*Close all the files that opens*/
    for(i=0;i<NOFILE;i++)
            close(i);
    /*Change the working directory into /tmp*/
    chdir("/tmp");
    /*Reset the file mask*/
    umask(0);
    return;
    }
        
int main(int argc, char** argv)
{
    FILE *fp;
    time_t log_time;
    //init_deamon();
	/*This place is the fork of the program & Then to excute another function*/
	/*
     ------------------------------------------------------------------------
	int status;
	pid_t chpid;
	chpid=fork();
	if(chpid<0){
		exit(1);
	}
	else if(chpid==0){
    	  execl("/home/lovingmage/Desktop/metasploitavevasion-master/cip.py",NULL);
	  exit(0);
	}
	else {
	waitpid(chpid,&status,0);
	}
	---------------------------------------------------------------------------
    	*/
   	/*while(1)
    	{
        sleep(20);
        
        if((fp=fopen("Graph.log","a"))>=0)
        {
            log_time=time(0);
            fprintf(fp,"Im here at %s",asctime(localtime(&log_time)));
            fclose(fp);
            }
	}
	*/
        
        
        /*-----------------------------------/
        /Set init vars of socket connection  /
        /               START                /
        /-----------------------------------*/
	
	    int    listenfd, connfd;
	    struct sockaddr_in     servaddr;
	    char    buff[4096];
	    int     n;
	    /*END of socket addrs init*/
	    /*Create init socket function*/
	    init_deamon();
	    
	    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
	    //printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
	    if((fp=fopen("/home/lovingmage/Desktop/Graph_Error.log","a"))>=0)
		    {
		        log_time=time(0);
		        fprintf(fp,"%s ->INIT DEAMON SOCKET LISTENFD ERROR.",asctime(localtime(&log_time)));
		        fclose(fp);
			exit(0);
		    }
	    exit(0);
	    }

	    memset(&servaddr, 0, sizeof(servaddr));
	    servaddr.sin_family = AF_INET;
	    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	    servaddr.sin_port = htons(6666);

	    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
	    //printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
	    if((fp=fopen("/home/lovingmage/Desktop/Graph_Error.log","a"))>=0)
		    {
		        log_time=time(0);
		        fprintf(fp,"%s ->SOCKET BIND ERROR.",asctime(localtime(&log_time)));
		        fclose(fp);
		    }
	    exit(0);
	    }
		 /*Ready for Accept Connection*/
	   
	    if( listen(listenfd, 10) == -1){
	    
	    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
	    exit(0);
	    }
	    if((fp=fopen("/home/lovingmage/Desktop/Graph.log","a"))>=0)
		{
		    log_time=time(0);
		    fprintf(fp,"%s ->Ready for Accept out connection Server connection Estavlish.",asctime(localtime(&log_time)));
		    fclose(fp);
		}
	    //printf("======waiting for client's request======\n");
	    while(1){
	    if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
		//printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
		if((fp=fopen("Graph_Error.log","a"))>=0)
		        {
		            log_time=time(0);
		            fprintf(fp,"%s ->ACCEPT CONNECT ERROR.",asctime(localtime(&log_time)));
		            fclose(fp);
		        }        
		continue;
	    }
	    n = recv(connfd, buff, MAXLINE, 0);
	    buff[n] = '\0';
	    if((fp=fopen("Socket.log","a"))>=0)
		    {
		        log_time=time(0);
		        fprintf(fp,buff,asctime(localtime(&log_time)));
		        fclose(fp);
		    }
	    //printf("recv msg from client: %s\n", buff);
	    close(connfd);
	    }

	  close(listenfd);
 	
}
