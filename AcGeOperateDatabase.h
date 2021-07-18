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
	bool getInforFromDatabase(CString database_tableName);//获取数据
	bool findDataByPara(CString database_tableName);
	bool insertDataToDatabase(CString database_tableName,  std::vector<std::vector<CString>>insertData);//插入数据
	bool deleteDataFromDatabase(CString database_tableName,CString fieldName,CString delete_para);//删除数据

public:
	MYSQL m_sqlCon;
	//字段名
	std::vector<CString>m_fieldList;
};

//std::vector<DatabaseTableFiledType>filedTypeList,

