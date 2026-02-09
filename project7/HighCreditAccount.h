#pragma once
#ifndef __HIGHCREDIT_ACCOUNT_H__
#define  __HIGHCREDIT_ACCOUNT_H__

#include "NormalAccount.h"

class HighCreditAccount : public NormalAccount //신용계좌 개설_NormalAccount 클래스 상속
{
private:
	int specialRate;
public:
	HighCreditAccount(int ID, int money, char* name, int rate, int special) : NormalAccount(ID, money, name, rate), specialRate(special)//NomalAccount 클래스 상속
	{
	}
	virtual void Deposit(int money)//가상함수(virtual) 설정 해서 동적 바인딩 하게 함(서로 다른 내용 가지기)
	{
		NormalAccount::Deposit(money); //원금과 이자추가
		Account::Deposit(money * (specialRate / 100.0)); //특별이자 계산 후 추가
	}
};
#endif