#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <climits>

class Customer
{
public:
	static int Counter;
	//Customer(std::string username, std::string password, std::string firstName, std::string lastName);
	Customer(std::string username, std::string password, std::string firstName, std::string lastName, std::string number, int balance);
	//Customer(const Customer& c);
	Customer() { balance = 0; }
	std::string getUsName();
	std::string getPsw();
	std::string getFName();
	std::string getLName();
	std::string getNumber();
	std::string getStrBalance();
	int getIntBalance();

	bool Deposit(int sum, std::string& message);
	bool Withdrawal(int sum, std::string& message);


	//Customer& operator = (Customer& c);

private:
	std::string username, password, firstName, lastName, number;
	int balance;
};


#endif // !CUSTOMER_H
