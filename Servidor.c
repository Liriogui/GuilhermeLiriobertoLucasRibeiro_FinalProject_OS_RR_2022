#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Função projetada para chat entre cliente e servidor.
void func(int connfd)
{
	char buff[MAX];
	int n;
	// loop infinito para o chat
	for (;;) {
		bzero(buff, MAX);

		// le a mensagem do cliente e copia no buffer
		read(connfd, buff, sizeof(buff));
		// imprime buffer que contém o conteúdo do cliente
		printf("From client: %s\t To client : ", buff);
		bzero(buff, MAX);
		n = 0;
		// copia a mensagem do servidor no buffer
		while ((buff[n++] = getchar()) != '\n')
			;

		// e envia esse buffer para o cliente
		write(connfd, buff, sizeof(buff));

		// se a msg contiver "Exit" então sai do servidor e o chat terminou.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Função do driver
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// criação e verificação do socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	//atribui IP, PORTA
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Vinculando o soquete recém-criado ao IP e verificação fornecidos
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Agora o servidor está pronto para escutar e verificar
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening...\n");
	len = sizeof(cli);

	// Aceita o pacote de dados do cliente e verificação
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Função para conversar entre cliente e servidor
	func(connfd);

	// Depois de conversar fecha o socket
	close(sockfd);
}