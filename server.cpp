
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>

int main()
{
    int socket_t,client_socket;
    struct sockaddr_in server_addr,client_addr;
    int server_len,client_len;
    char rcv_buf[BUFSIZ];
    char send_buf[BUFSIZ];
    char buf[BUFSIZ];
    int fd;

   
//---------------------------socket create-----------------------------------//

    socket_t=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socket_t)
    {
        perror("socket create fail...\n");
        exit(EXIT_FAILURE);
    }
    printf("socket create success...\n");
    
//---------------------------socket bind-----------------------------------//
    
   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_len=sizeof(server_addr);
    
    if(-1==bind(socket_t,(struct sockaddr*)&server_addr,server_len))
    {
        perror("bind fail ...\n");
        exit(EXIT_FAILURE);
    }
    else
    printf("socket bind success...\n");

//---------------------------socket listen-----------------------------------//

    if(-1==listen(socket_t,5))
    {
        perror("socket listen fail...\n");
        exit(EXIT_FAILURE);
    }else
     printf("socket listen success...\n");


//---------------------------socket accept-----------------------------------//

    client_len=sizeof(client_addr);
    
    
        client_socket=accept(socket_t,(struct sockaddr*)&client_addr,&client_len);
        if(client_socket!=-1)
        {   
            printf("accept success...\n");
           // printf("cliet from %s connected...\n", inet_ntoa(client_addr.sin_addr));
        }


//---------------------------socket process-----------------------------------//



    while(1)
    {
        
        if(read(client_socket,rcv_buf,BUFSIZ))
        {
            if(strcmp(rcv_buf,"quit")==0)
            {
                break;
            }
            sprintf(buf,"%s >info.txt",rcv_buf);
            system(buf);

            memset(buf,'\0',BUFSIZ);
            memset(rcv_buf,'\0',BUFSIZ);

            fd=open("info.txt",O_RDWR);

            read(fd,send_buf,BUFSIZ);

            write(client_socket,send_buf,BUFSIZ);
           
            memset(send_buf,'\0',BUFSIZ);

        }


    }
   
	unlink("info.txt");
    close(client_socket);
    close(socket_t);

    exit(EXIT_SUCCESS);
}
