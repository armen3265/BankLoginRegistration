#include "Customer.h"

Customer::Customer(std::string username, std::string password, 
	std::string firstName, std::string lastName, std::string number, int balance)
{
	Counter++;
	this->username = username;
	this->password = password;
	this->firstName = firstName;
	this->lastName = lastName;
	this->balance = balance;
	if (number == "")
	{
		//if account is a new, create a new number.
		this->number = std::to_string(Counter);
	}
	else
	{
		this->number = number;
	}
	
}

std::string Customer::getUsName()
{
	return this->username;
}

std::string Customer::getPsw()
{
	return this->password;
}

std::string Customer::getFName()
{
	return this->firstName;
}

std::string Customer::getLName()
{
	return this->lastName;
}

std::string Customer::getNumber()
{
	return this->number;
}

std::string Customer::getStrBalance()
{
	return std::to_string(balance);
}

int Customer::getIntBalance()
{
	return this->balance;
}

bool Customer::Deposit(int sum, std::string& message)
{
	if (balance + sum > INT_MAX)
	{
		message = "Your money has reached the maximum.";
		return false;
	}
	balance += sum;
	return true;	
}

bool Customer::Withdrawal(int sum, std::string& message)
{
	if (sum > balance)
	{
		message = "There is not enough money in your account.";
		return false;
	}
	balance -= sum;
	return true;
}
