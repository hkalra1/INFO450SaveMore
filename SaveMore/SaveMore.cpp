// SaveMore.cpp : Defines the entry point for the console application.

// Harry Kalra

#include "stdafx.h"
#include <stdio.h>
#include <iostream> 

using namespace std;

class BankAccount
{
public:
	const char *acctType = new char[25];
	const char *acctNumber = new char[14];
	double rate = 0;
	double balance = 0;
	int compound;

	void display();
	virtual int deposit(double dAccount);
	virtual int withdraw(double wAccount);
};


void BankAccount::display()
{

	cout << endl;

	cout << "Account Number: " << acctNumber << endl;
	cout << "Account Type: " << acctType << endl;
	cout << "Interest Rate: " << rate << '%' << endl;
	cout << "Account Balance: " << balance << endl;

}
int BankAccount::deposit(double dAccount)
{
	if (dAccount >= 0)
	{
		balance += dAccount;
		return 0;
	}
	else
	{
		cout << "Unable to Process transaction" << endl;
		return -1;
	}
}

int BankAccount::withdraw(double wAccount)
{
	if (balance - wAccount > 0)
	{
		balance -= wAccount;
		return 0;
	}
	else
	{
		cout << "You don't have money for that!!" << endl;
		return -1;
	}
}


class SavingsAccount : public BankAccount
{
public:
	SavingsAccount()
	{

	}
	void checkaccount()
	{
		if (balance >= 10000)
		{
			rate = 2;
		}
		else
		{
			rate = 1;
		}
	}
	void compoundInterest(int compound)
	{
		if (compound == 1)
		{
			balance = balance * (rate / 100);
			checkaccount();
		}
	}
	int deposit(double dAccount)
	{
		BankAccount::deposit(dAccount);
		checkaccount();
		return (0);
	}
	int withdraw(double wAccount)
	{
		BankAccount::withdraw(wAccount);
		checkaccount();
		return (0);
	}
};

class CheckingAccount : public BankAccount
{
public:
	CheckingAccount()
	{
		rate = 0;
	}
	void checkaccount()
	{
		if (balance < 500)
		{
			balance = balance - 5;
		}
	}
	void orderChecks()
	{
		balance = balance - 15.00;
	}
	int deposit(double dAccount)
	{
		BankAccount::deposit(dAccount);
		checkaccount();
		return (0);
	}
	int withdraw(double wAccount)
	{
		BankAccount::withdraw(wAccount);
		checkaccount();
		return (0);
	}
};


class cd : public BankAccount
{
public:
	int term;
	void checkterm(int tAccount)
	{
		if (tAccount >= 5)
			rate = 10;
		else
			rate = 5;
	}
	cd(int tAccount)
	{
		checkterm(tAccount);
		term = tAccount;

	}
	void compound(int compound)
	{
		if (compound == 1)
		{
			balance = balance + (balance * (rate / 100));
		}
	}
	void fine(int fine)
	{
		if (fine == 1)
		{
			balance = (balance - (balance *(rate / 100)));
		}
	}
	int deposit(double dAccount)
	{
		BankAccount::deposit(dAccount);
		checkterm(term);
		return (0);

	}
	int withdraw(double wAccount, int i)
	{
		if (i == 1)
		{
			balance = (balance - (balance *(rate / 100)));
		}
		BankAccount::withdraw(wAccount);
		checkterm(term);
		return (0);
	}
};

int main()
{
	cout << "SaveMore Bank" << endl;
	cout << "-----------------------------------" << endl;
	SavingsAccount savings;
	savings.acctNumber = "1010167855068";
	savings.acctType = "Saving";
	savings.deposit(10000);							//create a new savings account and deposit $10K
	CheckingAccount checking;
	checking.acctNumber = "1010167855214";
	checking.acctType = "Checking";
	checking.deposit(600);							//create a new checking account and deposit $600
	cd cd(3);
	cd.acctNumber = "1010167855598";
	cd.deposit(10000);								//create a new CD account with a 3 year term and deposit $10K
	cd.acctType = "Certificate of Deposit";
	savings.display();
	checking.display();
	cd.display();
	savings.compoundInterest(1);
	cd.compound(1);
	savings.display();
	cd.display();
	checking.orderChecks();							//order checks
	checking.withdraw(200);							//withdraw $200 from checking
	savings.withdraw(1000);							//withdraw $1000 from Savings
	cd.withdraw(2000, 1);							//Perform an early withdrawal of $2000 from the CD Account
	savings.display();
	checking.display();
	cd.display();
}