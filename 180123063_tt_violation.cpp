
#include <bits/stdc++.h>
#include <mysql.h>
using namespace std;

char const *host = "localhost";
char const *user = "root";
char const *pass = "1234";
char const *dbname = "180123063_26may2020";

unsigned int port = 3306;
const char *unix_socket = NULL;
unsigned int flag = 0;
int main()
{
  MYSQL *conn;
  conn = mysql_init(NULL);
  if(!mysql_real_connect(conn,host,user,pass,dbname,port,unix_socket,flag))
  {
  	fprintf(stderr,"Error : %s [%d] \n",mysql_error(conn),mysql_errno(conn));
  	exit(1);
  }
  printf("Connected !!! \n");
  mysql_query(conn,"select * from ett");
  MYSQL_RES *res1;
  MYSQL_ROW row1;
  res1 = mysql_store_result(conn);
  int num_fields1 = mysql_num_fields(res1);
  vector <vector <string>> m1; 
  while(row1 = mysql_fetch_row(res1))
  {
  	vector <string> v1;
  	for(int i=0;i<num_fields1;i++) 
  	{
  		v1.push_back((string)row1[i]);
  	}
  	m1.push_back(v1);
  }
  mysql_free_result(res1);
  set <pair<string,string>> s1;
  for(int i=0;i<m1.size();i++)
  {
	
  	for(int j=0;j<m1.size();j++)
  	{
  		if(i==j) continue;
  		if(m1[i][1]<=m1[j][1]) continue; 
  		if(m1[i][2] == m1[j][2] && m1[i][3] == m1[j][3])
  		{
  			s1.insert(make_pair(m1[i][1],m1[j][1]));
  			//cout << m1[i][1] << m1[j][1] << endl;
  		}  
  	}
  }
  
  mysql_query(conn,"select t1.rno,t1.name,t1.cid,t2.cid from cwsl as t1 join cwsl as t2 where t1.rno = t2.rno and t1.cid>t2.cid");
  MYSQL_RES *res;
  MYSQL_ROW row;
  res = mysql_store_result(conn);
  int num_fields = mysql_num_fields(res);
  int cnt = 0;
  while(row = mysql_fetch_row(res))
  {
  	string rno = row[0];
  	string name = row[1];
  	string cid1 = row[2];
  	string cid2 = row[3];

  	if(s1.find(make_pair(row[2],row[3])) !=s1.end())
  	{
  		cout << rno << " " << name << " " << cid1 << " " << cid2 << endl;
  		string f1 = "insert into ans1 values(\"" + rno + "\",\"" + name + "\",\"" + cid1 + "\",\"" + cid2 + "\")";
  		const char *f2 = f1.c_str(); 
  		mysql_query(conn,f2);
  		cnt++;
  	} 
  }
  cout << "Number of rows returned = " << cnt << endl;
  mysql_free_result(res);
  mysql_close(conn);
  return 0;
}
