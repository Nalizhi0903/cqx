#include <stdio.h>
#include <mysql/mysql.h>
#include <unistd.h>
int main()
{
    MYSQL my;
    mysql_init(&my);
    //连接接数据库
    mysql_real_connect(&my, "192.168.163.132", "cqx", "cqxctz123", "ChatSystem", 3306, NULL, 0); 
    /*
    const char* str = "insert into user_info(userid, nickname, school, telnum, passwd) value (1,'cqx', 'bite', '13672678168', 'cqxctz123');";
    mysql_query(&my, str);//执行mysql插入语句
    */
    /*
     *获取结果集
     */
    MYSQL_RES* res;//结果集，指向了查询的结果信息
    mysql_query(&my, "select * from user_info;");
    res = mysql_store_result(&my);
    if(res == NULL)
    {
        printf("获取结果集失败\n");
        return 0;
    }
    int rows = mysql_num_rows(res);//获取结果集函数
    if(rows <= 0)
    {
        printf("结果集当中没有数据");
        return 0;
    }
    else 
    {
        printf("%d rows\n",rows);
    }
    for(int i = 0; i < rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(res);//获取结果集下一行的信息
        printf("%s,%s,%s,%s,%s\n", row[0], row[1], row[2], row[3], row[4]);
    }
    mysql_free_result(res);//释放结果集
    mysql_close(&my);//释放操作句柄
    //编译链接 -lmysqlclient
    while(1)
    {

    }
}
