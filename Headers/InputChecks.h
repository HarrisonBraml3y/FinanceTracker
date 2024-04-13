#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

class InputChecks {
private:
protected:
public:


	bool Login(std::string Email, std::string Password);
	double GenerateAccount();
	void Register();
	void Reset();
	double UpdateBalance(double Account, double NewValue);


};







class WriteToFile {
private:
protected:
public:
	double Balance;
	double In;
	double Output;

	WriteToFile();

	std::string FilePath = "C:\\Users\\harri\\Desktop\\FinanceTrackerSheet.xlsx";
	std::ofstream Write;
	std::ifstream FileIn;

	void Input();


	//void Summary(){}

	void WriteTo(double In, double Out);

	double Add(double& In);

	double Subtract(double& In);

	double LogIn();

	~WriteToFile();
};



class SqlConnect {
private:
protected:
public:
	SQLHANDLE SqlConnectionHandle;
	SQLHANDLE SqlStmtHandle;
	SQLHANDLE SqlEnvHandle;
	SQLCHAR RetCode[8192];
	SQLRETURN ReturnCode = 0;

	void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
	bool Connect();

	template<typename T>
	T RunQuery(const char* Query);
	template<>
	std::string RunQuery<std::string>(const char* Query);
	 
};