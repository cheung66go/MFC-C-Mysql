#include "stdafx.h"
#include "AcGeOperateDatabase.h"

AcGeOperateDatabase::AcGeOperateDatabase()
{
	mysql_init(&m_sqlCon);//初始化数据库对象
}


AcGeOperateDatabase::~AcGeOperateDatabase()
{
	mysql_close(&m_sqlCon);//关闭Mysql连接  
}

bool AcGeOperateDatabase::connectMysql(CString &username, CString &password, CString &databaseName,const int database_port)
{
	if (!mysql_real_connect(&m_sqlCon, "localhost", username, password, databaseName, database_port, NULL, 0))//localhost:服务器地址，可以直接填入IP;root:账号;123:密码;test:数据库名;3306:网络端口  
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		return true;
	}

}

bool AcGeOperateDatabase::getInforFromDatabase(CString database_tableName)
{
	mysql_query(&m_sqlCon, "SET NAMES gbk");//设置数据库字符格式，解决中文乱码问题
	
	findDataByPara(database_tableName);

	MYSQL_RES *res = mysql_store_result(&m_sqlCon);//得到存储结果集  
	if (NULL == res)//如果为空则返回
	{
		return false;
	}

	//列数
	unsigned int cols = mysql_num_fields(res);

	//获取数据行数
	int rows=0;
	rows=mysql_affected_rows(&m_sqlCon);


	for (int i = 0; MYSQL_FIELD *fd = mysql_fetch_field(res); i++)  
		m_fieldList.push_back(fd->name);

	// 获取列数
	int j = mysql_num_fields(res);  

	std::vector<std::vector<CString>>dataTotalList;
	int listrow = 0;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))//重复读取行，把数据放入列表中，直到row为NULL  
	{
		std::vector<CString>fieldList;
		for (int rols = 0; rols < cols; rols++)
		{
			CString myreaddata(row[rols]);
			fieldList.push_back(myreaddata);
		}
		dataTotalList.push_back(fieldList);
		listrow++;
	}
	
	mysql_free_result(res);

	return false;
}

bool AcGeOperateDatabase::findDataByPara(CString database_tableName)
{
	CString tempSql = "select * from " + database_tableName;
	if (mysql_real_query(&m_sqlCon, tempSql, tempSql.GetLength()) == 1)// 查询数据库中的特定表  //1是失败，0是成功
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	return true;
}

bool AcGeOperateDatabase::insertDataToDatabase(CString database_tableName, std::vector<std::vector<CString>>insertData)
{
	CString temSql = "INSERT " + database_tableName + " (";
	if (m_fieldList.size() <= 0)
		return false;
	for (int i = 0; i < m_fieldList.size()-1; i++)
	{
		temSql += m_fieldList[i];
		temSql += ",";
	}
	temSql += m_fieldList[m_fieldList.size() - 1];
	temSql += ")";
	temSql += "VALUES";
	
	for (int m = 0; m < insertData.size(); m++)
	{
		CString temSqlSeg = "(";
		for (int n = 0; n < insertData[m].size(); n++)
		{
			temSqlSeg += "\"";
			temSqlSeg += insertData[m][n];
			if (n != insertData[m].size() - 1)
			{
				temSqlSeg += "\",";
			}
			else
				temSqlSeg += "\"";
	    }
		if (m!=insertData.size()-1)
		{
			temSqlSeg += "),";
		}
		else
			temSqlSeg += ");";
		temSql += temSqlSeg;
     }
	if (mysql_real_query(&m_sqlCon, temSql, temSql.GetLength()) == 1)//   //1是失败，0是成功
	{
		CString temp= mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	return true;
}

bool AcGeOperateDatabase::deleteDataFromDatabase(CString database_tableName,CString fieldName, CString delete_para)
{
	CString tempSql = "delete  from " + database_tableName+ " where "+fieldName+" = "+ delete_para;
	if (mysql_real_query(&m_sqlCon, tempSql, tempSql.GetLength()) == 1)// 查询数据库中的特定表  //1是失败，0是成功
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	return true;
}


