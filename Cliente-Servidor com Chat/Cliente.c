#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(void){
    char caractere [100];
    int sockfd;
    struct sockaddr_in servaddr;
    FILE *myf = fopen("Conversação_Cliente.txt", "a");
    time_t t;
    struct tm *tm;
    char hora [100];
    char *tmp;
    char sendline [100] = "Usando a porta 22000\n";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero (&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (22000);

    inet_pton(AF_INET,"172.17.0.1", &(servaddr.sin_addr));
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    printf("\n\n\t\t------Chat Inicializado------\n\n");
    fputs("\n\n\t\t------Chat Inicializado------\n\n", myf);

    while (!strstr(caractere, "Até") && !strstr(sendline, "Até")){
        bzero(caractere, 100);
        t = time(NULL);
        tm = localtime (&t);
        strftime (hora, 100, "\n Eu (%H:%M) -> ", tm);
        printf("%s", hora);
        fgets (sendline, 100, stdin);
        tmp = strcat(hora, sendline);
        fputs (tmp, myf);
        write(sockfd, sendline, strlen(sendline)+1);
        if(!strstr(caractere, "Até")){
            strftime (hora, 100, "\n Servidor (%H:%M) -> ", tm);
            read (sockfd, caractere, 100);
            tmp = strcat (hora, caractere);
            printf("%s", tmp);
            fputs (tmp, myf);
    }
}
printf("\n\n Bate Papo finalizado\n");
printf("\n O arquivo foi gerado-> Conversa_Cliente.txt.txt");
fclose(myf);
}
