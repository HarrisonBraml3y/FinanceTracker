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



	bool Test;
	//Test = Sql.RunQuery<bool>("SELECT TOP 1 1 FROM FinanceTrackerSheet WHERE Email = 'harrison-bramley@hotmail.com'");
	//std::cout << "Test:" << Test << std::endl;
	std::string Exists;
	Test = Sql.RunQuery<bool>("SELECT TOP 1 'exists' FROM FinanceTrackerSheet WHERE Email = 'harrison-bramley@hotmail.com'");
	std::cout << Test << std::endl;
/*
	std::string Bal = Sql.RunQuery<std::string>("SELECT Email FROM FinanceTrackerSheet");
	std::cout << Bal << std::endl;

	int Choice;


	std::vector<std::string> Emails;
	std::vector<std::string> Passwords;
	std::string EmailIn;
	std::string PasswordIn;

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

	*/
}