#include "stdafx.h"
#include "AppTransData.h"
#include "AppClient.h"
#include "AcGeOperateDatabase.h"
void AppTransData::init()
{
	AppClient::RegistCommand(AppTransData::getDataFromMySql,"AppTransData::getDataFromMySql","getdatafrommysql",false);
	AppClient::RegistCommand(AppTransData::deleteDataToDatabse, "AppTransData::deleteDataToDatabse", "deletedatafrommysql", false);
}

void AppTransData::getDataFromMySql()
{
	AcGeOperateDatabase operate;
	CString username="root", password="618618", databaseName="db_model_para";
	if (operate.connectMysql(username, password, databaseName)!=true)
	{
		AfxMessageBox(_T("数据库连接失败!"));
	}
	CString tempTableName = "tb_design";//"tb_blastres";
	operate.getInforFromDatabase(tempTableName);

}

void AppTransData::inserDataToDatabse()
{
	AcGeOperateDatabase operate;
	CString username = "root", password = "618618", databaseName = "db_model_para";
	if (operate.connectMysql(username, password, databaseName) != true)
	{
		AfxMessageBox(_T("数据库连接失败!"));
	}
	std::vector<std::vector<CString>>insertData;
	std::vector<CString>tempData;
	std::vector<DatabaseTableFiledType>filedTypeList;
	for (int i = 0; i < 29; i++)
	{
		tempData.push_back("5.6");
		filedTypeList.push_back(kFiledTypeCString);
	}
	std::vector<CString>tempData2;
	for (int i = 0; i < 29; i++)
	{
		tempData2.push_back("60");
	}
	CString tempTableName = "tb_design";//"tb_blastres";
	insertData.push_back(tempData);
	insertData.push_back(tempData2);
	if (operate.insertDataToDatabase(tempTableName, insertData) == true)
	{
		AfxMessageBox("插入成功");
	}
}

void AppTransData::deleteDataToDatabse()
{
	AcGeOperateDatabase operate;
	CString username = "root", password = "618618", databaseName = "db_model_para";
	if (operate.connectMysql(username, password, databaseName) != true)
	{
		AfxMessageBox(_T("数据库连接失败!"));
	}
	CString tempTableName = "tb_design";
	CString tempFileName = "hole_number";
	if (operate.deleteDataFromDatabase(tempTableName, tempFileName, "6")==true)
	{
		AfxMessageBox("删除成功");
	}

}
