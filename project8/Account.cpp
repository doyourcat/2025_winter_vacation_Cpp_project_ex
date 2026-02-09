#define _CRT_SECURE_NO_WARNINGS
#include "BankingCommonDecl.h"
#include "Account.h"


Account::Account(int ID, int money, char* name) : accID(ID), total_money(money) //이름을 바꿔주기
{
	cusName = new char[strlen(name) + 1];
	strcpy(cusName, name);
}

Account::Account(const Account& ref) : accID(ref.accID), total_money(ref.total_money) //이름을 복사 생성자로 바꿔주기
{
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy(cusName, ref.cusName);
}

Account& Account::operator=(const Account& ref) //project7의 Account.cpp에서 추가된 정의) 대입 연산자 오버로딩
{
	accID = ref.accID; //ID 값 복사
	total_money = ref.total_money; //total_money 값 복사

	delete[]cusName; //기존 메모리 해제
	cusName = new char[strlen(ref.cusName) + 1]; //새 메모리 할당(new 사용)_이름 길이만큼 새로운 공간을 만듦
	strcpy(cusName, ref.cusName); //내용복사
	return *this; //자기 자신을 반환_operator의 반환형이 참조형이기 때문에 자기 자신을 참조형으로 반환해야 그 반환값이 다음 연산에서 사용될 수 있음
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

void Account::ShowAccInfo() const //전체 정보 출력
{
	cout << "계좌ID: " << accID << endl;
	cout << "이름: " << cusName << endl;
	cout << "잔액: " << total_money << endl;
}

Account::~Account()
{
	delete[]cusName; //메모리 할당 해제
}
