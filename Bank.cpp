#include "Bank.h"

Bank::Bank()
{
	// When opening the program, it checks if there is a list of users in our file.
	//add data to json file
	ifstream ifs(accJsonStr);
	if (ifs.is_open())
	{
		ifs >> j;
		ifs.close();
	}

	if (!j.is_null())
	{
		//Cicle foreach for json file
		for(auto acc : j)
		{
			//We take files from json, do decryption and add them to the "map"
			std::string number = acc["number"];
			int key = std::stoi(number);
			int balance = std::stoi(string_xor(acc["balance"],key));
			string username = string_xor(acc["username"], key);
			string password = string_xor(acc["password"], key);
			string firstName = string_xor(acc["firstName"], key);
			string lastName = string_xor(acc["lastName"], key);
			accounts[username] = Customer(username, password, firstName, lastName, number, balance);

			
			if (Customer::Counter < std::stoi(number))
			{
				Customer::Counter = std::stoi(number);
			}
		}
	}
}

void Bank::ViewPersonInformation()
{
	cout << "\tAccount Information\n\n";
	cout << "\nUsername: " << person->getUsName() << "\n";
	cout << "\nFirst Name: " << person->getFName() << "\n";
	cout << "\nLast Name: " << person->getLName() << "\n";
	cout << "\nPersonal Number: " << person->getNumber() << "\n";
	cout << "\nBalance: " << person->getIntBalance() << " $" << "\n";
}

void Bank::ViewAllAccounts()
{
	//View all accounts username and PersonalNumbers
	cout << "\tAll Accounts\n\n";
	cout << "\nOnly " << accounts.size() << " users in the bank.\n\n";
	for (auto it = accounts.begin(); it != accounts.end(); it++)
	{
		cout << "Personal Number: " << it->second.getNumber() << "\tUsername: " << it->second.getUsName() << endl;
	}
}

string Bank::GetPersonName()
{
	return person->getFName();
}

string Bank::GetUsername()
{
	return person->getUsName();
}

int Bank::GetPersonBalance()
{
	return person->getIntBalance();
}

string Bank::GetPersonalNumber()
{
	return person->getNumber();
}

void Bank::saveInJson(Customer* c1, Customer* c2)
{
	//when you close the program, add all the data to our file, in the json format

	int key = std::stoi(c1->getNumber());
	string username = c1->getUsName();

	j[username]["username"] = string_xor(username,key);
	j[username]["password"] = string_xor(c1->getPsw(),key);
	j[username]["firstName"] = string_xor(c1->getFName(),key);
	j[username]["lastName"] = string_xor(c1->getLName(),key);
	j[username]["number"] = c1->getNumber();
	j[username]["balance"] = string_xor(c1->getStrBalance(),key);

	if(c2!=nullptr)
	{
		key = std::stoi(c2->getNumber());
		string username = c2->getUsName();

		j[username]["username"] = string_xor(username,key);
		j[username]["password"] = string_xor(c2->getPsw(),key);
		j[username]["firstName"] = string_xor(c2->getFName(),key);
		j[username]["lastName"] = string_xor(c2->getLName(),key);
		j[username]["number"] = c2->getNumber();
		j[username]["balance"] = string_xor(c2->getStrBalance(),key);
	}


	std::ofstream ofs(accJsonStr);
	if (ofs.is_open())
	{
		ofs << setw(4) << j;
		ofs.close();
	}
	else
	{
		std::cout << "Failed to save data to file.";
	}
}


bool Bank::Registration(std::string username, string password)
{
	string check = accounts[username].getUsName();
	if (!check.empty())
	{
		return false;
	}

	string firstName, lastName;
	cout << "\nYour first name: ";
	cin >> firstName;

	cout << "\nYour last name: ";
	cin >> lastName;


	//The program itself gives the initial balance
	accounts[username] = Customer(username, password, firstName, lastName, "",300000);
	
	saveInJson(&accounts[username],nullptr);

	return true;
}

bool Bank::LogIn(string username, string password)
{
	if (accounts[username].getUsName() == username && accounts[username].getPsw() == password)
	{
		ChangePerson(username);
		return true;
	}
	else
	{
		cout << "\nIncorrect username or password entered.\n";
		return false;
	}
}

int Bank::GetUsersCount()
{
	return accounts.size();
}

void Bank::ChangePerson(string username)
{
	person = &accounts[username];
}

bool Bank::Deposit(string sum)
{
	string message;
	srand(time(NULL));
	cout << "\tDeposit\n\n";
	if(!checkInt(sum) || std::stoi(sum) < 0)
	{
		cout << "\nSorry! You entered an incorrect amount!\n";
		return false;
	}

	int sumInt = std::stoi(sum);
	cout << "\nPlease answer the question correctly to complete the operation\n";

	int a = rand() % 10 + 1;
	int b = rand() % 10 + 1;

	int answer;
	cout << a << " x " << b << " = ";
	cin >> answer;
	if (answer != a * b)
	{
		cout << "\nSorry your answer is not correct.\n Deposit is failed.\n";
		return false;
	}

	if (!person->Deposit(sumInt, message))
	{			cout << "\n" << message << "\n";
		return false;
	}

	
	cout << "\nCongratulations! You have successfully made a deposit!\n";
	saveInJson(person,nullptr);
	return true;
}


bool Bank::Transaction(string& message)
{
	if (person == nullptr)
	{
		throw runtime_error("\nSomething went wrong!\n");
	}
	cout << "\tTransaction\n\n";
	string username;
	cout << "\nPlease write Username you want to send: ";
	cin>> username;
	if (username == person->getUsName())
	{
		message = "You can't send yourself.";
		return false;
	}
	if (accounts[username].getUsName().empty())
	{
		message = "User does not exist by this name";
		return false;
	}
	string sum;
	cout << "\nPlease write the amount you want to send: ";
	cin >> sum;

	if(!checkInt(sum))
	{
		message = "Sorry! You entered an incorrect amount!";
		return false;
	}
	int sumInt = std::stoi(sum);
	if (!person->Withdrawal(sumInt, message))
	{
		return false;
	}
	if (!accounts[username].Deposit(sumInt,message))
	{
		return false;
	}
	message += "You sent " + sum + " to " + accounts[username].getUsName() + "\n";
	saveInJson(person, &accounts[username]);
	return true;
}


void Bank::RemoveAccount()
{
	string username = person->getUsName();
	accounts.erase(username);
	j.erase(username);
	person = nullptr;

	std::ofstream ofs(accJsonStr);
	if (ofs.is_open())
	{
		ofs << setw(4) << j;
		ofs.close();
	}
	else
	{
		std::cout << "Failed to save data to file.";
	}
}
