#include "offlinemessagemodel.hpp"
#include "db.hpp"

void OfflineMsgModel::insert(int userid, string msg)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values('%d','%s')",userid,msg.c_str());
    Mysql mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

void OfflineMsgModel::remove(int userid)
{
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "delete from offlinemessage where userid=%d",userid);
        Mysql mysql;
        if (mysql.connect())
        {
            mysql.update(sql);
        }
}

vector<string> OfflineMsgModel::query(int userid)
{
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "select message from offlinemessage where userid = %d ", userid);
        Mysql mysql;
        vector<string> vec;
        if (mysql.connect())
        {
            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                //把userid用户的所有离线消息放入vec中返回
                MYSQL_ROW row;
                while((row=mysql_fetch_row(res))!=nullptr)
                {
                    vec.push_back(row[0]);
                }
                mysql_free_result(res);
             }
        }
        return vec;
}
