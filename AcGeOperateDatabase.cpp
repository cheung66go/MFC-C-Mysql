#include "stdafx.h"
#include "AcGeOperateDatabase.h"

AcGeOperateDatabase::AcGeOperateDatabase()
{
	mysql_init(&m_sqlCon);//��ʼ�����ݿ����
}


AcGeOperateDatabase::~AcGeOperateDatabase()
{
	mysql_close(&m_sqlCon);//�ر�Mysql����  
}

bool AcGeOperateDatabase::connectMysql(CString &username, CString &password, CString &databaseName,const int database_port)
{
	if (!mysql_real_connect(&m_sqlCon, "localhost", username, password, databaseName, database_port, NULL, 0))//localhost:��������ַ������ֱ������IP;root:�˺�;123:����;test:���ݿ���;3306:����˿�  
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	else//���ӳɹ�������������ݿ⣬֮�����ز�����������Ƿ����������
	{
		return true;
	}

}

bool AcGeOperateDatabase::getInforFromDatabase(CString database_tableName)
{
	mysql_query(&m_sqlCon, "SET NAMES gbk");//�������ݿ��ַ���ʽ�����������������
	
	findDataByPara(database_tableName);

	MYSQL_RES *res = mysql_store_result(&m_sqlCon);//�õ��洢�����  
	if (NULL == res)//���Ϊ���򷵻�
	{
		return false;
	}

	//����
	unsigned int cols = mysql_num_fields(res);

	//��ȡ��������
	int rows=0;
	rows=mysql_affected_rows(&m_sqlCon);


	for (int i = 0; MYSQL_FIELD *fd = mysql_fetch_field(res); i++)  
		m_fieldList.push_back(fd->name);

	// ��ȡ����
	int j = mysql_num_fields(res);  

	std::vector<std::vector<CString>>dataTotalList;
	int listrow = 0;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))//�ظ���ȡ�У������ݷ����б��У�ֱ��rowΪNULL  
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
	if (mysql_real_query(&m_sqlCon, tempSql, tempSql.GetLength()) == 1)// ��ѯ���ݿ��е��ض���  //1��ʧ�ܣ�0�ǳɹ�
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
	if (mysql_real_query(&m_sqlCon, temSql, temSql.GetLength()) == 1)//   //1��ʧ�ܣ�0�ǳɹ�
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
	if (mysql_real_query(&m_sqlCon, tempSql, tempSql.GetLength()) == 1)// ��ѯ���ݿ��е��ض���  //1��ʧ�ܣ�0�ǳɹ�
	{
		CString temp = mysql_error(&m_sqlCon);
		AfxMessageBox(temp);
		return false;
	}
	return true;
}


