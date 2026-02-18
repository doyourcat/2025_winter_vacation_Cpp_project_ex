#pragma once
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include "String.h" //String 클래스 있는 헤더파일 불러오기

class Account
{
private:
	int accID;
	int total_money;
	String cusName; //project8에서 쓰이던 포인터 대신 String 클래스를 활용
public:
	Account(int ID, int money, String name);
	//Account 클래스의 레퍼런스 함수 선언과 형 변환 연산자(operator) 삭제

	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
	//project8에서는 앞에서 동적 할당된 메모리 주소를 가진 포인터가 있었기에 뒤에서 ~(소멸자)Account를 사용해서 메모리를 소멸시켜줌
	//하지만 앞에서 메모리 할당이 이루어지지 않았기 때문에 삭제
	
};
#endif