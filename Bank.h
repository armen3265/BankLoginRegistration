#pragma once

#include "includeLibrarys.h"

using json = nlohmann::json;
using namespace std;

class Bank
{
private:
	map<string, Customer> accounts;
	string accJsonStr = "accounts.json";
	void saveInJson(const Customer* c1, const Customer* c2);
	Customer* person = nullptr;
	void ChangePerson(const string& username);
	json j;
public:
	Bank();

	void ViewPersonInformation();
	void ViewAllAccounts();
	string GetPersonName() const;
  string GetUsername() const;
	int GetPersonBalance() const;
	string GetPersonalNumber() const;

	bool Deposit(string sum);
	bool Transaction(string& message);
	bool Registration(const string& username,const string& password);
	bool LogIn(const string& username,const string& password);
	void RemoveAccount();
	
	int GetUsersCount();
};