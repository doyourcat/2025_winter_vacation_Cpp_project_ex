#pragma once

#ifndef __NORMAL_ACCOUNT_H__
#define __NORMAL_ACCOUNT_H__

#include "Account.h"

class NormalAccount : public Account //보통 예금계좌 개설_Account 클래스 상속
{
private:
	int interRate; //이자율
public:
	NormalAccount(int ID, int money, char* name, int rate) : Account(ID, money, name), interRate(rate) {}
	virtual void Deposit(int money) //부모 클래스인 Account에서 상속받았으나 가상함수(virtual)를 설정해서 동적 바인딩을 하게 함(서로 다른 내용을 가져야 하므로)
	{
		Account::Deposit(money); //원금 추가
		Account::Deposit(money * (interRate / 100.0)); //이자율 계산하고 추가
	}

};
#endif