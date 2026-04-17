#include<iostream>
#include<mysql/mysql.h>
#include <ostream>
#include <string>
using namespace std;
int main()
{
    MYSQL* conn=mysql_init(nullptr);
    if(!conn)
    {
        cout<<"连接失败"<<endl;
        return 1;
    }
    MYSQL*tem=mysql_real_connect(
            conn, 
            "127.0.0.1",
            "Daixusheng", 
            "123456", 
            "user_audit_system",
            3306, 
            nullptr,
            0);
    if(!tem)
    {
        cout<<"连接失败"<<endl;
        cout<<"语句执行失败"<<mysql_error(conn)<<endl;
        return 1;
    }
    conn=tem;
    cout<<"连接成功"<<endl;
    string name="张三";
    cout<<"请输入你要查询的用户"<<endl;
    cin>>name;
    string sql="select id,username,role from users where username='"+name+"'";
    cout<<"你要执行的sql语句为:"<<sql<<endl;
    cout<<"准备执行mysql_query"<<endl;
    int ret=mysql_query(conn,sql.c_str());
    cout<<"mysql_query执行完成了，ret="<<ret<<endl;
    if(ret!=0)
    {
         cout<<"语句执行失败"<<mysql_error(conn)<<endl;
         mysql_close(conn);
         return 1;
    }
    MYSQL_RES*res=mysql_store_result(conn);
    if(res==nullptr)
    {
        cout<<"语句执行失败"<<mysql_error(conn)<<endl;
        return 1;
    }
    unsigned int num=mysql_num_fields(res);
    cout<<"有"<<num<<"列"<<endl;
    MYSQL_ROW row;
    bool found=false;
    while((row=mysql_fetch_row(res))!=nullptr)
     {
         found=true;
        for(int i=0;i<num;i++)
         {
            cout<<row[i]<<" ";
         }
        cout<<endl;
    }
    if(found==false)
    {
        cout<<"没有查询到数据!"<<endl;
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
