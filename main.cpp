#include "Bank.h"

int Customer::Counter = 0;


#define pauseLinux system("read -p 'Press Enter to continue...' var");
#define clearLinux system("clear");
#define pauseWindows system("pause");
#define clearWindows system("clear");

int main()
{
	#ifdef _WIN32
 		clearWindows;
	#elif __linux__
    	clearLinux;
	#endif

	Bank bank;

	cout << "\tHi dear user. ";
	while (true)
	{
		cout<<"Please login or registration.\n\n\n";
		cout << "Press 1 for Login\nPress 2 for Registration\nPress 3 for exit program\n\n";
		int choice;
		cout<<"Your choice: ";
		cin >> choice;
		if (choice == 1)
		{
			cout << "\nYour username: ";
			string username;
			cin >> username;

			cout << "\nYour password: ";
			string password;
			cin >> password;
			if (!bank.LogIn(username, password))
			{
				#ifdef _WIN32
 					pauseWindows;
					clearWindows;
				#elif __linux__
    				pauseLinux;
					clearLinux;
				#endif

				continue;
			}
			cout << "\n\n\n";

			#ifdef _WIN32
 				pauseWindows;
				clearWindows;
			#elif __linux__
    			pauseLinux;
				clearLinux;
			#endif
			
			cout << "Hello dear " << bank.GetPersonName() << "\n\n\n\n";
			bool login = true;
			while (login)
			{ 
				cout << "Balance: " << bank.GetPersonBalance() << "\t\tPersonal Number: " << bank.GetPersonalNumber()<< "\n\n";

				cout << "Press 1 for View account\n";
				cout << "Press 2 for View all accounts\n";
				cout << "Press 3 for Deposit\n";
				cout << "Press 4 for Transaction\n";
				cout << "Press 5 for Remove account\n";
				cout << "Press 6 for Log Out\n\n\n\n";
				
				cin >> choice;
				
				cout << "\n\n";
				string TransacitonMessage;
				string remove;
				string depositSum;

				#ifdef _WIN32
					clearWindows;
				#elif __linux__
					clearLinux;
				#endif

				switch (choice)
				{
				case 1:
					bank.ViewPersonInformation();
					break;
				case 2:
					bank.ViewAllAccounts();
					break;
				case 3:
					cout << "\nPlease write the amount to add to your account: ";
					cin >> depositSum;
					bank.Deposit(depositSum);
					break;
				case 4:
					if (bank.Transaction(TransacitonMessage))
					{
						cout << "\nThe transaction was successful!\n" << TransacitonMessage << "\n";
					}
					else
					{
						cout << "\nAn error occurred during a transaction\nCause: " << TransacitonMessage << "\n";
					}
					break;
				case 5:
					cout<<"\nPlease write YES for remove or NO for cancel.\n";
					cin>>remove;

					if(remove == "Yes" || remove == "YES" || remove == "yes")
					{
						bank.RemoveAccount();
						cout<<"\nYour account has been removed!\n";
					}
					
				default:
					login = false;
				}


				#ifdef _WIN32
 			   		pauseWindows;
					clearWindows;
				#elif __linux__

    				pauseLinux;
					clearLinux;
				#endif
				
			}
		}
		else if (choice == 2)
		{
			cout << "\nYour username: ";
			string username;
			cin >> username;

			cout << "\nYour password: ";
			string password;
			cin >> password;

			if (!bank.Registration(username, password))
			{
				cout << "\n\n\nUser with this username already exists\nPlease come up with a different username!\n";
			}
			else
			{
				cout << "\n\nCongratulations!You have successfully registered. Login to your account using \"Login\"\n\n\n\n\n";
			}

			#ifdef _WIN32
 				pauseWindows;
				clearWindows;
			#elif __linux__
    			pauseLinux;
				clearLinux;
			#endif

			continue;
		}
		else
		{
			break;
		}
	}
}
