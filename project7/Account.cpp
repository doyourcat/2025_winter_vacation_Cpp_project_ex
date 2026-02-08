#include "BankingCommonDecl.h"
#include "Account.h"


Account::Account(int ID, int money, char* name) : accID(ID), total_money(money) //이름을 바꿔주기
{
	cusname = new char[strlen(name) + 1];
	strcpy(cusname, name);
}

Account::Account(const Account& ref) : accID(ref.accID), total_money(ref.total_money) //이름을 복사 생성자로 바꿔주기
{
	cusname = new char[strlen(ref.cusname) + 1];
	strcpy(cusname, ref.cusname);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money) //총 금액에 입금할 금액 더해주기
{
	total_money += money;
}

int Account::Withdraw(int money) //총 금액에 출금할 금액 빼주기
{
	if (total_money < money)
		return 0;
	total_money -= money;
	return money;
}

void Account::showAccInfo() const //전체 정보 출력
{
	cout << "계좌ID: " << accID << endl;
	cout << "이름: " << cusname << endl;
	cout << "잔액: " << total_money << endl;
}

Account::~Account()
{
	delete[]cusname; //메모리 할당 해제
}
