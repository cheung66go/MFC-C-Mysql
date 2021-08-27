#pragma once
#include "mysql.h"
#include <vector>

//enum DatabaseTableFiledType
//{
//	kFiledTypeInt = 0,
//	kFiledTypeCString = 1,
//	kFiledTypeDouble = 2,
//	kHaveNoValue=3
//};

//struct ParaData
//{
//	DatabaseTableFiledType type;
//	int a;
//	CString s;
//	double b;
//};

class AcGeOperateDatabase
{
public:
	AcGeOperateDatabase();
	~AcGeOperateDatabase();
	bool connectMysql(CString &m_username, CString &m_password, CString &databaseName,const int database_port= 3306);
	//获取字段名称和表内的所有数据，更换表之后需要使用该函数来获取新的字段数据，默认获取数据
	bool preInforFromDatabase(CString database_tableName, std::vector<std::vector<CString>>&dataTotalList, std::vector<CString>fieldNameList = {}, std::vector<CString>paraList = {},bool isGetData=true);
	bool insertDataToDatabase(CString database_tableName,  std::vector<std::vector<CString>>insertData);//插入数据
	bool deleteDataFromDatabase(CString database_tableName,CString fieldName,CString delete_para);//删除数据
	bool setFiledData(std::vector<CString>filedList);//设置字段名称

private:
	bool findDataByPara(CString database_tableName,
		std::vector<CString>fieldNameList = {}, std::vector<CString>paraList = {});
public:
	bool getFiledNameList(std::vector<CString>&filedList);
private:
	MYSQL m_sqlCon;
	//字段名
	std::vector<CString>m_fieldList;
};

