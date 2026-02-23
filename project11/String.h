#pragma once

#ifndef __STRING_H__
#define __STRING_H__

#include "BankingCommonDecl.h"

// 문자열을 안전하고 편리하게 관리하기 위한 사용자 정의 String 클래스
class String
{
private:
	int len; // 문자열의 길이 (널 문자 '\0' 포함)
	char* str; // 동적 할당된 문자열 메모리를 가리키는 포인터
public:
	//1) 생성자와 소멸자
	String(); //기본 생성자(빈 문자열 생성)
	String(const char* s); //문자열을 인자로 받는 생성자
	String(const String& s); //복사 생성자(깊은 복사)
	~String(); //동적 할당된 메모리 해제

	//2) 연산자 오버로딩
	String& operator= (const String& s); //깊은 복사, 기존 메모리 해제
	String& operator+= (const String& s); //기존 문자열 뒤에 이어 붙이기
	bool operator== (const String& s); //문자열 내용 같은지 비교
	String operator+ (const String& s); //두 문자열을 합친 새로운 객체를 반환


	//전역함수(Friend를 사용)
	// 클래스 외부의 함수지만, private 멤버(str)에 접근할 수 있도록 권한을 부여함
	friend ostream& operator<< (ostream& os, const String& s); //cout << s
	friend istream& operator>> (istream& is, String& s); //cin >> s
};
#endif
