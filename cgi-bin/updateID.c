#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
int main(int argc, char const *argv[])
{
    MYSQL mysql;
    int ret = 1;
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
    char *tokens[4];
    data = getenv("QUERY_STRING");

    char *token = strtok(data, ":");
    int i = 0;

    while (token != NULL && i < 4)
    {
        tokens[i] = token;
        token = strtok(NULL, ":");
        i++;
    }

    sprintf(cmd, "select * from user_Table where user_card_id = '%s';", tokens[0]);
    ret = mysql_real_query(sql, cmd, strlen(cmd));
    MYSQL_RES *res = mysql_store_result(sql);
    if (res != NULL)
    {
        unsigned int row = mysql_num_rows(res);
        if (row == 0)
            printf("error");
        else
        {
            sprintf(cmd, "update user_Table set user_name = '%s',user_address = '%s',phone_num = '%s' where user_card_id = '%s';",
                    tokens[1], tokens[2], tokens[3], tokens[0]);
            ret = mysql_real_query(sql, cmd, strlen(cmd));
            if (ret == 0)
                printf("ok");
        }
    }
    mysql_free_result(res);
    mysql_close(sql);
    return 0;
}
