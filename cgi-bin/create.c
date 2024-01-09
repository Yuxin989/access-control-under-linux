#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
int main(int argc, char const *argv[])
{
    MYSQL mysql;
    int ret = 0;
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
        if (strcmp(tokens[0], "") == 0 || strcmp(tokens[1], "") == 0 || strcmp(tokens[2], "") == 0)
        {
            printf("用户名或密码不可为空!");
        }
        else if (strcmp(tokens[1], tokens[2]) != 0)
        {
            printf("两次密码不相同!");
        }
        else
        {
            sprintf(cmd, "insert into administrator values('%s','%s');", tokens[0], tokens[1]);
            ret = mysql_real_query(sql, cmd, strlen(cmd));
            if (ret == 0)
                printf("ok");
        }
    }

    mysql_close(sql);
    return 0;
}
