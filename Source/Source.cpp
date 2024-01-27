#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "Headers/InputChecks.h"


//Below is method to populate sql search results
std::vector<std::string> TestQuery(std::vector<std::string> In) {
	std::vector<std::string> Strings = { "1", "2", "3" };
	std::vector<std::string> ReturnValue;
	for (int i = 0; i != 3; i++) {
		In.push_back(Strings[i]);
	}
	return In;
}



int main() {
	InputChecks Input;
	WriteToFile WriteTo;
	SqlConnect Sql;
	int Choice;

	std::vector<std::string> Emails;
	std::vector<std::string> Passwords;
	std::string EmailIn;
	std::string PasswordIn;



	std::vector<std::string>VectorString = TestQuery(VectorString);
	std::vector<char> TestVec;
	Sql.SQLQuery("SELECT Account FROM FinanceTrackerSheet;", VectorString);
	//TestVec.push_back(TestQuery);

	for (const auto& i : VectorString) {
		std::cout << i << std::endl;

	}
	
	std::cout << "Welcome, would you like to login to an existing account or create an account?\n";
	std::cin >> Choice;

	switch (Choice) {
	case 1:
		std::cout << "To proceed to login, please provide your email and password\n";
		std::cout << "Email: ";
		std::cin >> EmailIn;
		std::cout << "\n Password: ";
		std::cin >> PasswordIn;

		Input.Login(Emails, Passwords, EmailIn, PasswordIn);
		break;
	case 2:
		Input.Register();
		break;
	}


}