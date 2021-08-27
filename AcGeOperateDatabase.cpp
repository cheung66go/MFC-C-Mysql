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

bool AcGeOperateDatabase::connectMysql(CString &m_username, CString &m_password, CString &databaseName,const int database_port)
{
	if (!mysql_real_connect(&m_sqlCon, "159.138.49.84", m_username, m_password, databaseName, database_port, NULL, 0))//localhost:服务器地址，可以直接填入IP;root:账号;123:密码;test:数据库名;3306:网络端口  
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	else//连接成功则继续访问数据库
	{
		return true;
	}

}

bool AcGeOperateDatabase::preInforFromDatabase(CString database_tableName,\
	std::vector<std::vector<CString>>&dataTotalList, std::vector<CString>fieldNameList, std::vector<CString>paraList,bool isGetData )
{
	dataTotalList.clear();
	mysql_query(&m_sqlCon, "SET NAMES gbk");//设置数据库字符格式，解决中文乱码问题
	
	findDataByPara(database_tableName, fieldNameList,paraList);

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

	m_fieldList.clear();
	for (int i = 0; MYSQL_FIELD *fd = mysql_fetch_field(res); i++)  
		m_fieldList.push_back(fd->name);

	// 获取列数
	int j = mysql_num_fields(res);  

	if (isGetData == true)
	{
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
	}

	mysql_free_result(res);

	return true;
}


bool AcGeOperateDatabase::findDataByPara(CString database_tableName,\
	std::vector<CString>fieldNameList, std::vector<CString>paraList)
{
	CString tempSql="";
	if (fieldNameList .size()==0&& paraList .size()== 0)
	{
		tempSql = "select * from " + database_tableName;
	}
	else
	{
		tempSql = "select * from " + database_tableName + " where " ;
		for (int i=0;i<fieldNameList.size();i++)
		{
			if (i==fieldNameList.size()-1)
			{
				tempSql += database_tableName + "." + fieldNameList[i] + "=" + "\"" + paraList[i] + "\"" ;
			}
			else
			{
				tempSql += database_tableName + "." + fieldNameList[i] + "=" + "\"" + paraList[i] + "\""+" and ";
			}
		}
	}
	if (mysql_real_query(&m_sqlCon, tempSql, tempSql.GetLength()) == 1)// 查询数据库中的特定表  //1是失败，0是成功
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	return true;
}

bool AcGeOperateDatabase::getFiledNameList(std::vector<CString>& filedList)
{
	if (m_fieldList.size()==0)
	{
		return false;
	}
	filedList = m_fieldList;
	return true;
}

bool AcGeOperateDatabase::insertDataToDatabase(CString database_tableName, std::vector<std::vector<CString>>insertData)
{
	CString temSql = "INSERT ";
	temSql+=" INTO "+database_tableName + "(";
	if (m_fieldList.size() <= 0)
		return false;
	for (int i = 0; i < m_fieldList.size()-1; i++)
	{
		temSql += database_tableName+"."+m_fieldList[i];
		temSql += ",";
	}
	temSql += database_tableName + "."+m_fieldList[m_fieldList.size() - 1]+ ")";
	temSql +="VALUES";
	
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
		AfxMessageBox(temp+"请检查是否有重复数据");
		return false;
	}
	return true;
}

bool AcGeOperateDatabase::deleteDataFromDatabase(CString database_tableName,CString fieldName, CString delete_para)
{
	CString tempSql = "delete  from " + database_tableName + " where " + fieldName + " = " + R"(")"+delete_para +R"(")";
	if (mysql_real_query(&m_sqlCon, tempSql, tempSql.GetLength()) == 1)// 查询数据库中的特定表  //1是失败，0是成功
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	return true;
}

bool AcGeOperateDatabase::setFiledData(std::vector<CString> filedList)
{
	for (int i=0;i<filedList.size();i++)
	{
		m_fieldList.push_back(filedList[i]);
	}
	return false;
}


