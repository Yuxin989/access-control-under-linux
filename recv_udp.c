#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <mysql/mysql.h>
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
    char cmd[128] = "";
    while (1)
    {
        bzero(buf, sizeof(buf));
        recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
        printf("card_id: %s\n", buf);
        sprintf(cmd, "select * from user_Table where user_card_id = '%s';", buf);
        ret = mysql_real_query(sql, cmd, strlen(cmd));
        if (ret == 0)
        {
            MYSQL_RES *res = mysql_store_result(sql);
            if (res != NULL)
            {
                unsigned int col = mysql_num_fields(res);
                unsigned int row = mysql_num_rows(res);
                if (row > 0)
                {
                    MYSQL_ROW row_con;
                    row_con = mysql_fetch_row(res);
                    bzero(cmd, sizeof(cmd));
                    sprintf(cmd, "insert into user_Access(user_name,user_card_id,user_address,phone_num) values('%s','%s','%s','%s');",
                            row_con[0], row_con[1], row_con[2], row_con[3]);
                    ret = mysql_real_query(sql, cmd, strlen(cmd));
                    if (ret == 0)
                        printf("正常刷卡!\n");
                }
                else
                {
                    bzero(cmd, sizeof(cmd));
                    sprintf(cmd, "insert into Trespassing(card_id) values('%s');", buf);
                    ret = mysql_real_query(sql, cmd, strlen(cmd));
                    if (ret == 0)
                        printf("非法闯入!\n");
                }
            }
            mysql_free_result(res);
        }
    }
    close(sockfd);
    mysql_close(sql);

    return 0;
}
