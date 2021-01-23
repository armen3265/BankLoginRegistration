#pragma once
#ifndef BANK_H
#define BANK_H

#include "includeLibrarys.h"

using json = nlohmann::json;
using namespace std;

class Bank
{
	friend class PersonalArea;
private:
	map<string, Customer> accounts;
	string accJsonStr = "accounts.json";
	void saveInJson(Customer* c1, Customer* c2);
	Customer* person = nullptr;
	void ChangePerson(string username);
	json j;
 public:
	Bank();

	void ViewPersonInformation();
	void ViewAllAccounts();
	string GetPersonName();
	string GetUsername();
	int GetPersonBalance();
	string GetPersonalNumber();

	bool Deposit(string sum);
	bool Transaction(string& message);
	bool Registration(string username, string password);
	bool LogIn(string username, string password);
	void RemoveAccount();
	
	int GetUsersCount();
};



#endif // !BANK_H

