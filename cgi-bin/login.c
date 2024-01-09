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
    char *tokens[2];
    data = getenv("QUERY_STRING");
    if (data == NULL)
        printf("error1");
    else
    {
        char *token = strtok(data, ":");
        int i = 0;

        while (token != NULL && i < 2)
        {
            tokens[i] = token;
            token = strtok(NULL, ":");
            i++;
        }
        if (strcmp(tokens[0], "") == 0 || strcmp(tokens[1], "") == 0)
        {
            printf("用户名或密码不可为空!");
        }
        else
        {
            sprintf(cmd, "select * from administrator where admin_name = '%s';", tokens[0]);
            ret = mysql_real_query(sql, cmd, strlen(cmd));
            if (ret == 0)
            {
                MYSQL_RES *res = mysql_store_result(sql);
                if (res != NULL)
                {
                    unsigned int col = mysql_num_fields(res);
                    unsigned int row = mysql_num_rows(res);
                    MYSQL_ROW row_con;
                    row_con = mysql_fetch_row(res);
                    if (strcmp(tokens[1], (char *)row_con[1]) == 0)
                        printf("ok");
                }
                mysql_free_result(res);
            }
            else
                printf("用户未注册");
        }
    }
    mysql_close(sql);
    return 0;
}
