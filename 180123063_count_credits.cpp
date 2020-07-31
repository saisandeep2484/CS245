
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
  mysql_query(conn,"select t1.rno,t1.name,sum(t2.cred) as sum1 from cwsl as t1 join cc as t2 on t1.cid = t2.cid group by t1.rno,t1.name having sum1>40");
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
  for(int i=0;i<m1.size();i++)
  {
  	string rno = m1[i][0];
  	string name = m1[i][1];
  	string tot = m1[i][2];
	string f1 = "insert into ans2 values(\"" + rno + "\",\"" + name + "\"," + tot + ")";
	cout << rno << " " << name << " " << tot << endl;
	//cout << f1 << endl;
  	const char *f2 = f1.c_str(); 
  	mysql_query(conn,f2);
  }
 printf("Number of rows returned: %lu\n", (unsigned long)mysql_num_rows(res1));
  mysql_free_result(res1);
  mysql_close(conn);
  return 0;
}

