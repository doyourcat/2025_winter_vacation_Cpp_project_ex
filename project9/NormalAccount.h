#pragma once
#ifndef __NORMAL_ACCOUNT_H__
#define __NORMAL_ACCOUNT_H__

#include "Account.h"
#include "String.h"  //생성자의 매개변수 때문에 필요 NormalAccount(int ID, int money, String name ....

class NormalAccount : public Account
{
private:
	int interRate;   // 이자율 %단위
public:
	
	NormalAccount(int ID, int money, String name, int rate)
		: Account(ID, money, name), interRate(rate)
	{
	}
	virtual void Deposit(int money)
	{
		Account::Deposit(money);        // 원금추가
		Account::Deposit(money * (interRate / 100.0));   // 이자추가
	}
};
#endif
