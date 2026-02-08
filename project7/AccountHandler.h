#pragma once
#ifndef __ACCOUNT_HANDLER_H__
#define __ACCOUNT_HANDLER_H__

#include "Account.h"


class AccountHandler //계좌 관리 클래스
{
private:
	Account* accArr[100]; //배열 선언
	int accNum;

public:
	AccountHandler();
	void ShowMenu(void) const; //메뉴 출력
	void MakeAccount(void); //계좌 생성
	void DepositMoney(void); //입금
	void WithdrawMoney(void); //출금
	void ShowAllAccInfo(void) const; //모든 정보 출력
	~AccountHandler(); //동적 메모리 해제

protected:
	void MakeNormalAccount(void); //일반 계좌 
	void MakeCreditAccount(void); //신용 계좌
};
#endif
