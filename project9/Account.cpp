#include "BankingCommonDecl.h"
#include "Account.h"

Account::Account(int ID, int money, String name) //String 클래스로 name 받기
	: accID(ID), total_money(money)
{
	
	cusName = name;
}


int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)
{
	total_money += money;
}

int Account::Withdraw(int money)
{
	if (total_money < money)
		return 0;

	total_money -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "계좌ID: " << accID << endl;
	cout << "이  름: " << cusName << endl;
	cout << "잔  액: " << total_money << endl;
}

