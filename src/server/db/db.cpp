#include "db.hpp"
#include <muduo/base/Logging.h>
#include "chatserver.hpp"

//数据库配置信息
static string server = "localhost";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

Mysql::Mysql()
{
    _conn = mysql_init(nullptr);
}

Mysql::~Mysql()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}

bool Mysql::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        //C/C++默认字符编码为ASCII
        mysql_query(_conn, "set names gbk");
        LOG_INFO<< " connect mysql success!";
    }
    else
    {
        LOG_INFO << "Connection failed! " << mysql_error(_conn) ;
    }
    return p;
}

bool Mysql::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }
    return true;
}

MYSQL_RES *Mysql::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

MYSQL *Mysql::getConnection()
{
    return _conn;
}
