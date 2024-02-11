#include <iostream>
#include <fstream>
#include <vector>

#include "Headers/InputChecks.h"


SqlConnect Sql;

std::string FileToWrite = "C:\\Users\\harri\\Desktop\\FinanceTrackerSheet.csv";
std::ofstream Write;
std::ifstream WriteIn;

bool InputChecks::Login(std::vector<std::string> Emails, std::vector<std::string> Passwords, std::string Email, std::string Password) {
Start:

	std::cout << "Enter your e-mail address" << std::endl;
	std::cin >> Email;
	std::cout << "Enter your password" << std::endl;
	std::cin >> Password;


	std::cout << "Login()" << std::endl;
	std::cout << "Password[1] = " << Passwords[1] << std::endl;
	std::cout << "Emails[1] = " << Emails[1] << std::endl;
	for (int i = 0; i < Emails.size(); i++) {
		if (Email == Emails[i] && Password == Passwords[i]) {
			std::cout << "Logged in" << std::endl;
			return true;
		}

		else {
			std::cout << "Incorrect email or password." << std::endl;
			if (Email == Emails[i] && Password != Passwords[i]) {
				std::cout << "Would you like to reset your password?" << std::endl;
			}

			else {
				goto Start;
			}
			return false;
		}

	}
}
//Figure out how to get results into Accounts. Try +1 in while loop, as each execution should be +1 result.	//try having the function return the result
double InputChecks::GenerateAccount() {
	double Account{0};
	std::vector<double> Accounts;
	int Loop = 0;
	//std::rand(std::time(nullptr));
	//Problem here, function must return a value for it to be a condition
	while (Sql.RunQuery<double>("SELECT Account FROM FinanceTrackerSheet;")) {
		Loop++;
		Accounts.push_back(Sql.RunQuery<double>("SELECT Account FROM FinanceTrackerSheet;"));
	}


	Account = Sql.RunQuery<double>("SELECT Account FROM FinanceTrackerSheet ORDER BY Account DESC");
	
	return Account;
}

void InputChecks::Register() {
	std::string Email;
	std::string Password;
	std::string Temp;
	std::cout << "To register an account, begin by entering your e-mail address" << std::endl;
	std::cin >> Email;
	std::cout << "Now enter your password" << std::endl;
	std::cin >> Password;
	std::cout << "Re enter your password" << std::endl;
	std::cin >> Temp;
	if (Temp != Password) {
		std::cout << "Passwords do not match" << std::endl;
		return;
	}


	Write.open(FileToWrite, std::ios::app);
	if (!Write.is_open()) {
		std::cout << "Could not find the specified file path" << std::endl;
		return;
	}
	Write << Email << "," << Password << GenerateAccount() << std::endl;
	Write.close();
}

void InputChecks::Reset() {
	//rename in sql database for future use, 
	//take 
	std::string Email;
	std::string newPassword;

	std::string Query = "UPDATE Account SET Email" + Email + "Password" + newPassword;


}





WriteToFile::WriteToFile() {


}
WriteToFile::~WriteToFile() {

}

void WriteToFile::WriteTo(double In, double Out) {
	Write.open(FilePath, std::ios::app);
	if (!Write.is_open()) {
		return;
	}
	else {
		Write << In << "," << Out << std::endl;
		Write.close();
	}
}

double WriteToFile::Add(double& In) {
	//add checks etc.
	Balance += In;
	SqlConnect SqlFunctions;
	std::ostringstream BalanceString;
	BalanceString << Balance;
	std::string Query = ("INSERT INTO FinanceTrackerSheet (Account, Balance) VALUES('', '" + BalanceString.str() + "'); ");
	const char* QueryChar = Query.c_str();

	SqlFunctions.RunQuery<char>(QueryChar);

	std::cout << "Balance: " << Balance << std::endl;
	return In;
}

double WriteToFile::Subtract(double& In) {



	return In;
}

void WriteToFile::Input() {
	int Choice = 0;
	int Num;
	std::cout << "Would you like to log in or log out a sum?" << std::endl;
	switch (Choice) {
	case 1:
		std::cin >> Num;
		std::cout << "How much would you like to log in to your account?" << std::endl;
		std::cin >> In;
		Add(In);
		break;
	case 2:
		std::cin >> Num;

	}
}








//	SqlConnectionHandle = NULL;
//	SqlStmtHandle = NULL;
void SqlConnect::showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
		std::cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << std::endl;
}

bool SqlConnect::Connect() {
	SqlConnectionHandle = NULL;
	SqlStmtHandle = NULL;

	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SqlEnvHandle)) {
			break;
		}
		if (SQL_SUCCESS != SQLSetEnvAttr(SqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
			break;
		}
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SqlEnvHandle, &SqlConnectionHandle)) {
			break;
		}
		if (SQL_SUCCESS != SQLSetConnectAttr(SqlConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0)) {
			break;

		}

		std::cout << "Connecting to server" << std::endl;

		switch (SQLDriverConnect(SqlConnectionHandle, NULL, (SQLCHAR*)"Driver={ODBC Driver 17 for SQL Server};Server=DESKTOP-JTCPO7G\\MSSQLSERVER01;Database=Finance;UID=Testacc;PWD=2000;", SQL_NTS, RetCode, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
		case SQL_SUCCESS:
			std::cout << "SQL_SUCCESS" << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			return true;
			break;
		case SQL_SUCCESS_WITH_INFO:
			std::cout << "SQL_SUCCESS_WITH_INFO" << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			return true;

			break;
		case SQL_NO_DATA_FOUND:
			std::cout << "SQL_NO_DATA_FOUND " << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			ReturnCode = -1;
			return false;

			break;
		case SQL_INVALID_HANDLE:
			std::cout << "SQL_INVALID_HANDLE" << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			ReturnCode = -1;
			return false;
			break;

		case SQL_ERROR:
			std::cout << "SQL_ERROR" << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			ReturnCode = -1;
			return false;
			break;
		default:
			return false;
			break;
		}
	} while (FALSE);
}

template<typename T>
T SqlConnect::RunQuery(const char* Query) {
	T Result;
	std::vector<T> ResultVector;

	if (!Connect()) {
		std::cout << "No connection" << std::endl;
		return 0;
	}

	do {


		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SqlConnectionHandle, &SqlStmtHandle)) {
			// Allocates the statement
			break;
		}

		if (SQL_SUCCESS != SQLExecDirect(SqlStmtHandle, (SQLCHAR*)Query, SQL_NTS)) {	//sqlexecdirect will take statement handle, text and text length 
			// Executes a preparable statement
			std::cout << "Error executing query" << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			break;		//breaks here
		}
		else {

			std::cout << "Query executed" << std::endl;
			SQLRETURN FetchResult;
			std::cout << "else" << std::endl;
			char Balance[256];
			char Account[256];
			if (Query == "SELECT * FROM FinanceTrackerSheet;") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Balance, sizeof(Balance), NULL);


					std::cout << "Balance: " << Balance << std::endl;
					if (!ResultVector.empty()) {
						ResultVector.push_back(Balance);

					}

				}
			}

			if (Query == "SELECT Account FROM FinanceTrackerSheet;") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);


					std::cout << "Account " << Account << std::endl;
					if (!ResultVector.empty()) {
						ResultVector.push_back(Account);

					}
				}

				std::cout << "Final FetchResult: " << FetchResult << std::endl;
			}
			if (Query == "SELECT Account FROM FinanceTrackerSheet ORDER BY Account DESC") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 3, SQL_C_DEFAULT, &LastAccount, sizeof(LastAccount), NULL);
					return Result;
				}
			}
			return 1;
		}
	} while (FALSE);
}