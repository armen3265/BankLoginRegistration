#include "Customer.h"

Customer::Customer(const std::string& username,const std::string& password, 
const	std::string& firstName,const std::string& lastName,const std::string& number, int balance)
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

std::string Customer::getUsName() const
{
	return this->username;
}

std::string Customer::getPsw() const
{
	return this->password;
}

std::string Customer::getFName() const
{
	return this->firstName;
}

std::string Customer::getLName() const
{
	return this->lastName;
}

std::string Customer::getNumber() const
{
	return this->number;
}

std::string Customer::getStrBalance() const
{
	return std::to_string(balance);
}

int Customer::getIntBalance() const
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
