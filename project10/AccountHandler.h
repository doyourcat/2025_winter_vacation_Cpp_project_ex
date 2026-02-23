#pragma once

#ifndef __ACCOUN_HANDLER_H__
#define __ACCOUN_HANDLER_H__

#include "Account.h"
#include "BoundCheckArray.h"

class AccountHandler //게좌 관리 클래스
{
private:
	BoundCheckArray<Account*> accArr; //템플릿 클래스로 배열 관리 Account 객체의 주소를 담아야함
	int accNum; //새로운 계좌가 개설될 때, 빈 공간을 찾기 위한 인덱스 번호 역할(= 개설된 계좌가 몇 개인지 파악)
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
