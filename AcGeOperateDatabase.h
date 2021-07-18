#pragma once
#include "mysql.h"
#include <vector>

enum DatabaseTableFiledType
{
	kFiledTypeInt = 0,
	kFiledTypeCString = 1,
	kFiledTypeDouble = 2,
};
class AcGeOperateDatabase
{
public:
	AcGeOperateDatabase();
	~AcGeOperateDatabase();
	bool connectMysql(CString &username, CString &password, CString &databaseName,const int database_port= 3306);
	bool getInforFromDatabase(CString database_tableName);//��ȡ����
	bool findDataByPara(CString database_tableName);
	bool insertDataToDatabase(CString database_tableName,  std::vector<std::vector<CString>>insertData);//��������
	bool deleteDataFromDatabase(CString database_tableName,CString fieldName,CString delete_para);//ɾ������

public:
	MYSQL m_sqlCon;
	//�ֶ���
	std::vector<CString>m_fieldList;
};

//std::vector<DatabaseTableFiledType>filedTypeList,

