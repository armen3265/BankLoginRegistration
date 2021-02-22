#pragma once

#include <string>
#include <climits>

class Customer
{
public:
	static int Counter;
	Customer(const std::string& username,const std::string& password,
	const std::string& firstName,const std::string& lastName,const std::string& number, int balance);

	Customer() { balance = 0; }
	std::string getUsName() const;
	std::string getPsw() const;
	std::string getFName() const;
	std::string getLName() const;
	std::string getNumber() const;
	std::string getStrBalance() const;
	int getIntBalance() const;

	bool Deposit(int sum, std::string& message);
	bool Withdrawal(int sum, std::string& message);


	//Customer& operator = (Customer& c);

private:
	std::string username, password, firstName, lastName, number;
	int balance;
};