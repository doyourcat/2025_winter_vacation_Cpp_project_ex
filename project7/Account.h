#pragma once
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

//계좌 클래스 선언
class Account {
private:
	int accID;
	int total_money;
	char* cusname;

public:
	Account(int ID, int money, char* name); //기본 생성자

	Account(const Account& ref); //복사 생성자

	int GetAccID() const; //const를 붙임으로 멤버 변수를 안 바뀌게 함
	virtual void Deposit(int money); //나중에 상속받은 클래스에서 입금기능을 다르게 만들 수 있게 함(virtual) = 동적 바인딩
	int Withdraw(int money);
	void showAccInfo() const;
	~Account();
};
#endif