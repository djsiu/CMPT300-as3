// This program initiates lets-talk

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "list.c"
#include "list.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

// global variables


// function prototypes
void* keyboardThread(void* arg);
void* senderThread(void* arg);
void* receiverThread(void* arg);
void* printerThread(void* arg);

// thread 1 function: get input from keyboard, put message into list
void* keyboardThread(void* arg) {
	char myInput[4000]; // requirement: 4k characters
	
	// get input from keyboard 
	printf("Welcome to LetS-Talk! Please type your messages now.\n");
	//scanf("%[^\n]s",myInput);
	
	// put message into list
	
	
}

// thread 2 function: get message from list and send to another client
void* senderThread(void* arg) {
	
	// get input from keyboard 
	printf("senderThread.\n");

	
	// put message into list
	
	
}

// thread 3 function: put messages received from another client on the list
void* receiverThread(void* arg) {
	
	// get input from keyboard 
	printf("receiverThread.\n");

	
	// put message into list
	
	
}

// thread 4 function: remove messages from the list and print them on the console
void* printerThread(void* arg) {
	
	// get input from keyboard 
	printf("printerThread.\n");

	
	// put message into list
	
	
}

// main function
int main(int argc, char* argv[]) {
	
	
	int i = 0;
	char* local_port; // port numbers range from 0 to 65536
	char* IP_addr; // IP address has form d.d.d.d with 0<d<255
	char* remote_port; // port numbers range from 0 to 65536
	
	local_port = argv[1];
	IP_addr = argv[2];
	remote_port = argv[3];
	
	pthread_t keyboard_tid;
	pthread_t sender_tid;
	pthread_t receiver_tid;
	pthread_t printer_tid;
	
	int sockfd;
	struct sockaddr_in server_addr;
	socklen_t addr_size;
	int rc;
	int lenSendTo;
	int lenString;
	
	// >:(((
	char* hello = "Hello World";
	char buffer[4000];
	
	// errpr with command prompt
	if (argc != 4) {
		printf("Usage:\n");
		printf("  ./lets-talk <local port> <remote host> <remote port>\n");
		printf("Examples:\n");
		printf("  ./lets-talk 3000 192.168.0.513 3001\n");
		printf("  ./lets-talk 3000 some-computer-name 3001\n");
		return -1;
	}
	
	// start connection
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket creation failed");
		return -2; 
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(remote_port));
	server_addr.sin_addr.s_addr = inet_addr(IP_addr);
	
	rc = bind(sockfd,(const struct sockaddr*)&server_addr,sizeof(server_addr));
	if (rc == -1) {
		printf("failed to bind");
		return -3;
	}
	
	lenString = strlen(hello);
	
	
	bzero(buffer, 4000);
	addr_size = sizeof(server_addr);
	strcpy(buffer,"Hello World");
	
	
	lenSendTo = sendto(sockfd,buffer,lenString,0,(struct sockaddr*)&server_addr,addr_size);
	
	printf("The following message has been sent: %s\n",buffer);
	
	if (lenSendTo == -1) {
		printf("failed to send\n");
	}
	
	
	recvfrom(sockfd,buffer,lenString,0,(struct sockaddr*)&server_addr,&addr_size);
	
	printf("The following message has been received: %s\n",buffer);
	
	// thread 1: get input from keyboard
	if (pthread_create(&keyboard_tid,NULL,keyboardThread,NULL) != 0) {
		return 1;
	}
	
	if (pthread_join(keyboard_tid,NULL) != 0) {
		return 2;
	}
	
	// thread 2: get message from list and send to another client
	if (pthread_create(&sender_tid,NULL,senderThread,NULL) != 0) {
		return 3;
	}
	
	if (pthread_join(sender_tid,NULL) != 0) {
		return 4;
	}
	
	// thread 3: put messages received from another client on the list
	if (pthread_create(&receiver_tid,NULL,receiverThread,NULL) != 0) {
		return 5;
	}
	
	if (pthread_join(receiver_tid,NULL) != 0) {
		return 6;
	}
	
	// thread 4: remove messages from the list and print them on the console
	if (pthread_create(&printer_tid,NULL,printerThread,NULL) != 0) {
		return 7;
	}
		
	if (pthread_join(printer_tid,NULL) != 0) {
		return 8;
	}

	pthread_exit(NULL);
	
	return 0;
}