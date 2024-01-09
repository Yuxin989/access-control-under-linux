#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main(int argc, char const *argv[])
{
    MYSQL mysql;
    MYSQL *sql = mysql_init(&mysql);
    if (sql == NULL)
    {
        printf("mysql_init error");
        exit(-1);
    }
    sql = mysql_real_connect(sql, "10.9.42.212", "root", "111111", "ACS", 3306, NULL, 0);
    if (sql == NULL)
    {
        printf("mysql_real_connect error");
        exit(-1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(8000);
    myaddr.sin_addr.s_addr = inet_addr("10.9.42.212");
    int ret = 0;
    ret = bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
    if (ret != 0)
    {
        perror("bind");
        return -1;
    }
    char buf[1500] = "";
    bzero(buf, sizeof(buf));
    recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
    printf("buf = %s\n", buf);

    printf("Content-Type:text/html\n\n");
    char *data = NULL;
    char cmd[128] = "";
    char *tokens[3];
    data = getenv("QUERY_STRING");
    if (data == NULL)
        printf("error1");
    else
    {
        char *token = strtok(data, ":");
        int i = 0;

        while (token != NULL && i < 3)
        {
            tokens[i] = token;
            token = strtok(NULL, ":");
            i++;
        }
        sprintf(cmd, "insert into user_Table values('%s','%s','%s','%s');",
                tokens[0], buf, tokens[1], tokens[2]);
        ret = mysql_real_query(sql, cmd, strlen(cmd));
        if (ret == 0)
            printf("ok");
    }

    close(sockfd);
    mysql_close(sql);
    return 0;
}
