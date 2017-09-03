#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<string.h>  
      
int main()  
{  
    int fd[2];  
    if(socketpair(AF_LOCAL,SOCK_STREAM,0,fd)<0)
    {  
        perror("sockpair");  
        return 1;  
    }  
    pid_t id=fork();  
    if(id<0)
    {  
        perror("fork");  
        return 2;  
    }  
    else if(id==0)  
    {  
        close(fd[0]);  
        char buf[1024];  
        while(1)  
        {  
            strcpy(buf,"hello world");  
            write(fd[1],buf,strlen(buf));  
            ssize_t _s=read(fd[1],buf,sizeof(buf)-1);  
            buf[_s]='\0';  
            printf("father->child:%s\n",buf);  
            sleep(1);  
        }  
        close(fd[1]);  
    }  
    else  
    {  
        close(fd[1]);  
        char buf[1024];  
        while(1)  
        {  
            ssize_t _s=read(fd[0],buf,sizeof(buf)-1);  
            if(_s>0)  
            {  
                buf[_s]='\0';  
                printf("child->father:%s\n",buf);  
                sleep(1);  
            } 
		    
            strcpy(buf,"hello mygirl");  
            write(fd[0],buf,strlen(buf));  
		    sleep(1);
		
        }  
        close(fd[0]);  
      
    }  
    return 0;  
}  
