#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "Headers/InputChecks.h"





int main() {
	InputChecks Input;
	WriteToFile WriteTo;
	SqlConnect Sql;

	Sql.RunQuery<char>("SELECT * From FinanceTrackerSheet;");

	//char Last = Sql.RunQuery<char>("SELECT Balance From FinanceTrackerSheet WHERE Account = '3'");
	//std::cout << "Last: " << Last << std::endl;

	//double A = Sql.RunQuery<double>("SELECT Balance From FinanceTrackerSheet WHERE Account = '3'");	//error, returns Result as initialised. 
	//std::cout << "A: " << A << std::endl;
	int Choice;

	//int Test = 3;
	//std::string AccountString = std::to_string(Test);
	//std::cout << AccountString << std::endl;
	//std::string Temp = "SELECT Balance From FinanceTrackerSheet WHERE Account = '" + AccountString + "'";
	//const char* Query = Temp.c_str();
	//double NewBalance = Sql.RunQuery<double>(Query);


	//double test = Sql.RunQuery<double>("SELECT TOP 1 Account FROM FinanceTrackerSheet ORDER BY Account DESC");
	//std::cout << "test: " << test << std::endl;


	std::vector<std::string> Emails;
	std::vector<std::string> Passwords;
	std::string EmailIn;
	std::string PasswordIn;

	//std::vector<std::string>VectorString;
	//Sql.RunQuery("SELECT Account FROM FinanceTrackerSheet;", VectorString);
	////TestVec.push_back(TestQuery);
	//
	//for (const auto& i : VectorString) {
	//	std::cout << "Number of accounts: " << i << std::endl;
	//
	//}

	std::cout << "Would you like to login to an existing account or create an account?\n";
	std::cin >> Choice;

	switch (Choice) {
	case 1:
		std::cout << "To proceed to login, please provide your email and password\n";
		std::cout << "Email: ";
		std::cin >> EmailIn;
		std::cout << "\n Password: ";
		std::cin >> PasswordIn;

		//Input.Login(Emails, Passwords, EmailIn, PasswordIn);
		break;
	case 2:
		Input.Register();
		break;
	}


}