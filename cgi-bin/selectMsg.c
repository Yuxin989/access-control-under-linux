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
    char *token = strtok(data, ":");
    int i = 0;

    while (token != NULL && i < 2)
    {
        tokens[i] = token;
        token = strtok(NULL, ":");
        i++;
    }
    if (strcmp(tokens[0], "1") == 0)
        sprintf(cmd, "select * from user_Table where user_name = '%s';", tokens[1]);
    else if (strcmp(tokens[0], "2") == 0)
        sprintf(cmd, "select * from user_Table where user_card_id = '%s';", tokens[1]);
    else if (strcmp(tokens[0], "3") == 0)
        sprintf(cmd, "select * from user_Table where user_address = '%s';", tokens[1]);
    else if (strcmp(tokens[0], "4") == 0)
        sprintf(cmd, "select * from user_Table where phone_num = '%s';", tokens[1]);
    ret = mysql_real_query(sql, cmd, strlen(cmd));
    MYSQL_RES *res = mysql_store_result(sql);
    if (res != NULL)
    {
        unsigned int row = mysql_num_rows(res);
        if (row == 0)
            printf("error");
        else
        {
            unsigned int col = mysql_num_fields(res);
            MYSQL_ROW row_con;
            while (row_con = mysql_fetch_row(res))
            {
                for (int i = 0; i < col; i++)
                    printf("%s  ", (char *)row_con[i]);
            }
        }
    }
    mysql_free_result(res);

    mysql_close(sql);
    return 0;
}