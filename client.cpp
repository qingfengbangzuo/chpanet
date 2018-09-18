#include"../osapi/osapi.h"

#include<stdio.h>
#include<string.h>
#define BUFSIZE   8200
int main(int argc,char *argv[])
{

	if (argc != 2)
	{
		printf("please input : %s ipaddress port\n",argv[0]);
		return -1;
	}


	char send_buf[BUFSIZE];
	char rcv_buf[BUFSIZE];
	int running = 1;

	OS_TcpSocket client_sock;
	client_sock.Open();

	OS_SockAddr serv_addr(argv[1],8888);
	if (client_sock.Connect(serv_addr) < 0)
	{
		printf("can't connect the server!\n");
		return -1;
	
	}

	
	while (running)
	{
		printf(">>>");
		scanf("%[^\n]%*c",send_buf);

		int n = strlen(send_buf);
		client_sock.Send(send_buf, n);
		if (strcmp(send_buf, "quit") == 0)
		{
			break;
		}

		memset(send_buf, '\0', BUFSIZE);

		n = client_sock.Recv(rcv_buf, BUFSIZE);
		rcv_buf[n] = '\0';
		printf("%s\n", rcv_buf);


		memset(rcv_buf, '\0', BUFSIZE);
		

	}
	client_sock.Close();

	return 0;


}

