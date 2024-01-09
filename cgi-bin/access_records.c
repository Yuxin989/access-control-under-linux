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
    char cmd[128] = "select * from user_Access;";
    ret = mysql_real_query(sql, cmd, strlen(cmd));
    MYSQL_RES *res = mysql_store_result(sql);
    if (res != NULL)
    {
        unsigned int col = mysql_num_fields(res);
        MYSQL_ROW row_con;
        while (row_con = mysql_fetch_row(res))
        {
            for (int i = 0; i < col; i++)
                printf("%s  ", (char *)row_con[i]);
        }
        mysql_free_result(res);
    }
    mysql_close(sql);
    return 0;
}