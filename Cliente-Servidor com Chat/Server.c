#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

void main() {
	char caractere[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;
	FILE *myf = fopen("Conversação_servidor.txt", "a");
	time_t t;
	struct tm *tm;
	char hora[100];
	char *tmp;
	char sendline[ 100] = "Usando a porta 22000\n";

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22000);

	bind(listen_fd,(struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listen_fd, 10);
	comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

	printf("\n\n\t\t----Chat Inicializado----\n\n");
	fputs("n\n\t\t----Chat Inicializado------ - \n\n", myf);

	while(!strstr(caractere, "Até") && !strstr(sendline, "Até ")){
		bzero(caractere, 100);
		t = time(NULL);
		tm = localtime(&t);
		strftime(hora, 100, "\n Cliente (%H:%M) ->", tm);

		read(comm_fd, caractere, 100);
		tmp = strcat(hora, caractere);
		printf("%s", tmp);
		fputs (tmp, myf);
		if(!strstr(caractere,"Até")){
			strftime (hora, 100, "\n Eu (%H:%M) -> ", tm);
			printf("%s", hora);
			fgets(sendline, 100, stdin);
			tmp = strcat(hora, sendline);
			write(comm_fd, sendline, strlen(sendline)+1);
			fputs (tmp, myf);
	}
}
printf("\n\n Conversa finalizada \n");
printf("\n O arquivo foi gerado-> Conversa_servidor.txt.txt");
fclose(myf);
}
