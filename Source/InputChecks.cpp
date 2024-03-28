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

	std::string Temp = "SELECT Email FROM FinanceTrackerSheet where Email = '" + Email + "'";
	const char* QueryStr = Temp.c_str();
	if (!Sql.RunQuery<bool>(QueryStr)) {		//figure out if logged in, allow user to check accounts, edit accounts etc. 
		std::cout << "Account details not found" << std::endl;
		return false;
	}
	else {
		std::cout << "Logged in" << std::endl;
		std::cout << "> Update balance\n > Option2\n >Option3\n >Option4\n ";		//need funcs for each option, un-scattered 


		return true;
	}

}

double InputChecks::UpdateBalance(double Account, double NewValue) {
	SqlConnect Sql;
	std::string AccountString = std::to_string(Account);
	std::string NewValueString = std::to_string(NewValue);
	std::string GetString = "SELECT Balance FROM FinanceTrackerSheet WHERE Account = '" + AccountString + "'";
	const char* GetValue = GetString.c_str();
	double OldBalance = Sql.RunQuery<double>(GetValue);
	//double NewBalance = OldBalance + NewValue;
	std::string UpdateString = "UPDATE FinanceTrackerSheet SET Balance = " + NewValueString + " WHERE Account = '" + AccountString + "'";
	const char* Query = UpdateString.c_str();
	double NewBalance = Sql.RunQuery<double>(Query);
	std::cout << "Updated balance to: " << NewBalance << std::endl;
	return Account;
}


//Figure out how to get results into s. Try +1 in while loop, as each execution should be +1 result.	//try having the function return the result
double InputChecks::GenerateAccount() {
	double Account{ 0 };
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
	SQLCHAR Message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, Message, 1024, NULL))
	//if (SQL_INVALID_HANDLE == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, Message, 1024, NULL))
// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
std::cout << "SQL driver message: " << Message << "\nSQL state: " << SQLState << "." << std::endl;
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
	T Result{};
	std::vector<T> ResultVector;

	double Temp;

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
			break;
		}

		else {

			std::cout << "Query executed" << std::endl;
			SQLRETURN FetchResult;

			char Balance[256];
			char Account[256];
			char Text[256];

			if (Query == "SELECT * From FinanceTrackerSheet;") {
				std::cout << "Table:\n";
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS_WITH_INFO){
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Text, sizeof(Text), NULL);
					std::cout << Text << std::endl;
				}
				std::cout << "Final FetchResult: " << FetchResult << std::endl;

			}

			if (Query == "SELECT Account FROM FinanceTrackerSheet") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);
					std::cout << "Result: " << Account << std::endl;
					
				}
				return Result;

				std::cout << "Final FetchResult: " << FetchResult << std::endl;
			}

			if (Query == "SELECT TOP 1 Account FROM FinanceTrackerSheet") {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 1, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);
					std::cout << "Account: " << Account << std::endl;
			
				}
				return Result;
			}

			if (Query == "INSERT INTO FinanceTrackerSheet(Email, Password, Account, Balance) VALUES(2, 3, 4, 5)") {		//executes, but this runs false
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS) {
					SQLGetData(SqlStmtHandle, 3, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);

					return Result;
				}
			}

			if (Query == "SELECT Balance From FinanceTrackerSheet WHERE Account = '3'") {
				Connect();
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_INVALID_HANDLE) {		//returns sql_invalid_handle
					SQLGetData(SqlStmtHandle, 3, SQL_C_DEFAULT, &Result, sizeof(Result), NULL);
					std::cout << "SQLFetch result: " << FetchResult << std::endl; 
					std::cout << "Balance Result: " << Result << std::endl;

				}
				std::cout << "SQLFetch result: " << FetchResult << std::endl;

				return Result;
			}
			else {
				while ((FetchResult = SQLFetch(SqlStmtHandle)) == SQL_SUCCESS_WITH_INFO) {
					SQLGetData(SqlStmtHandle, 3, SQL_C_DEFAULT, &Account, sizeof(Account), NULL);
					std::cout << "Balance: " << Account << std::endl;

				}
				std::cout << "Executed" << std::endl;
			}
			return Result;
		}
	} while (false);

}