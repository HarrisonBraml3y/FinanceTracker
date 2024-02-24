#include <iostream>
#include <fstream>
#include <vector>

#include "Headers/InputChecks.h"


SqlConnect Sql;
std::string FileToWrite = "C:\\Users\\harri\\Desktop\\FinanceTrackerSheet.csv";
std::ofstream Write;
std::ifstream WriteIn;

bool InputChecks::Login(std::string Email, std::string Password) {
	SqlConnect Sql;
Start:

	std::cout << "Enter your e-mail address" << std::endl;
	std::cin >> Email;
	std::cout << "Enter your password" << std::endl;
	std::cin >> Password;
	if (!Sql.RunQuery<bool>("SELECT Email FROM FinanceTrackerSheet where Email = '" + Email + "'")) {	//email needds to be char


	}
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
//Figure out how to get results into s. Try +1 in while loop, as each execution should be +1 result.	//try having the function return the result
double InputChecks::GenerateAccount() {
	double Account{0};
	std::vector<double> Accounts;
	int Loop = 0;
	//std::rand(std::time(nullptr));
	//while (Sql.RunQuery<double>("SELECT Account FROM FinanceTrackerSheet;")) {
	//	Loop++;
	//	Accounts.push_back(Sql.RunQuery<double>("SELECT Account FROM FinanceTrackerSheet;"));
	//}


	Account = Sql.RunQuery<double>("SELECT TOP 1 Account FROM FinanceTrackerSheet ORDER BY Account DESC");
	
	return Account += 1;
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

	double AccountNo = GenerateAccount();
	std::cout << "Account number: " << AccountNo << std::endl;
	std::string AccountStr = std::to_string(AccountNo);
	std::string TempQuery = "INSERT INTO FinanceTrackerSheet (Email, Password, Account, Balance) VALUES ('" + Email + "', '" + Password + "', '" + AccountStr + "', '" + "0')";
	const char* QueryChar = TempQuery.c_str();

	Sql.RunQuery<double>(QueryChar);



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
	std::string Query = ("INTO FinanceTrackerSheet (Account, Balance) VALUES('', '" + BalanceString.str() + "'); ");
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
	std::cout << "Query: " << Query << std::endl;
	T Result;
	double Temp;

	if (!Connect()) {
		std::cout << "No connection" << std::endl;
		return 0;
	}


	do{
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SqlConnectionHandle, &SqlStmtHandle)) {
			// Allocates the statement
			break;
		}

		if (SQL_SUCCESS != SQLExecDirect(SqlStmtHandle, (SQLCHAR*)Query, SQL_NTS)) {	//sqlexecdirect will take statement handle, text and text length 
			// Executes a preparable statement
			std::cout << "Error executing query" << std::endl;
			showSQLError(SQL_HANDLE_STMT, SqlStmtHandle);
			break;
		}		

		else {

			std::cout << "Query executed" << std::endl;
			SQLRETURN FetchResult;

			char Balance[256];
			int Account[256];

			if (Query == "SELECT Account FROM FinanceTrackerSheet;") {							//this check if running each loop reglardless of the query
				std::cout << "X" << std::endl;
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS_WITH_INFO) {
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Result, sizeof(Result), NULL);
					std::cout << "Result: " << Result << std::endl;
					
					return Result;
				}

				std::cout << "Final FetchResult: " << FetchResult << std::endl;
			}

			if (Query == "SELECT TOP 1 Account FROM FinanceTrackerSheet ORDER BY Account DESC") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS_WITH_INFO) {
					SQLGetData(SqlStmtHandle, 3, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);
					for (auto i : Account) {
						std::cout << "Account: ";
			
						std::cout << i << std::endl;
						Result = i;
					}
					return Result;
				}
			}

			else {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 3, SQL_C_DEFAULT, &Result, sizeof(Result), NULL);
					return Result;
				}
				std::cout << "Executed" << std::endl;
			}
			return 1;
		}
	} while (false);

}
/*
std::vector<std::string> SqlConnect::RunQuery(const char* Query, std::vector<std::string>& StringVector) {

	if (!Connect()) {
		std::cout << "No connection" << std::endl;
		return StringVector;
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
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &StringVector, sizeof(StringVector), NULL);

				}
			}

			if (Query == "SELECT Account FROM FinanceTrackerSheet;") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);

					std::cout << "Account " << Account << std::endl;
					if (!StringVector.empty()) {
						std::string accountString(Account);
						StringVector.push_back(Account);

					}
					return StringVector;

				}
			}

		}
	} while (FALSE);

	return StringVector;
}*/