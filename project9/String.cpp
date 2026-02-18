#define _CRT_SECURE_NO_WARNINGS
#include "String.h"

String::String() //헤더파일의 String() 부분 범위지정
{
	len = 0;  
	str = NULL;
	//초기화
}

String::String(const char* s) //헤더파일의 String(const char* s) 부분 범위지정
{
	len = strlen(s) + 1;
	str = new char[len];
	strcpy(str, s);
	//길이를 증가시키고 새로운 문자열을 저장 후 copy해서 s에 저장
}

String::String(const String& s) // 헤더파일의 String(const String& s) 부분 범위지정
{
	len = s.len; //len 길이 가져오기
	str = new char[len]; //메모리 할당
	strcpy(str, s.str); //깊은 복사 copy
}

String::~String() // 헤더파일의 ~String() 부분 범위지정
{
	if (str != NULL) //str에 메모리가 있는 경우
		delete[]str; 
	//메모리 동적할당 해제
}

String& String::operator = (const String& s) // 헤더파일의 String& String::operator = (const String& s) 부분 범위지정
{
	if (str != NULL)
		delete[]str;//기존 가지고 있던 메모리 삭제
	len = s.len; 
	str = new char[len]; //s 크기만큼 새로운 공간 생성
	strcpy(str, s.str); //str 복사
	return *this; //this 포인터 사용해서 스스로를 반환
}

String& String::operator+= (const String& s) // 헤더파일의 String& String::operator += (const String& s) 부분 범위지정
{
	len += (s.len - 1); //전체 길이 계산(널 문자 중복 제거)
	char* tempstr = new char[len]; //더 큰 임시 공간 생성
	strcpy(tempstr, str); //기존의 내용 복사
	strcat(tempstr, s.str);//뒤에 이어서 복사

	if (str != NULL)
		delete[]str; //전에 있었던 메모리 해제
	str = tempstr; //임시 공간을 연결
	return *this;
}

bool String::operator== (const String& s) // 헤더파일의 String& String::operator == (const String& s) 부분 범위지정
{
	return strcmp(str, s.str) ? false : true;  // 0이면 false(다르다)가 아니라 true(같다)를 반환
	//안에 내용이 같은가를 확인
}

String String::operator+ (const String& s) // 헤더파일의 String& String::operator+ (const String& s) 부분 범위지정
{
	char* tempstr = new char[len + s.len - 1]; //합친 크기의 메모리를 준비
	strcpy(tempstr, str);
	strcat(tempstr, s.str);

	String temp(tempstr); //합친 문자열로 새로운 String 객체 생성
	delete[]tempstr; //임시 공간 해제
	return temp;//새 객체(temp)를 반환함, 이 때 원본은 그대로임
} 

// ostream& os는 cout을 가리키는 별명
ostream& operator<< (ostream& os, const String& s) // 헤더파일의 ostream& operator<< (ostream& os, const String& s) 부분 범위지정
{
	os << s.str; // cout에게 String 객체 말고, 그 안의 진짜 문자열(char*)을 출력하라고 시킴
	return os; // cout을 다시 반환 (그래야 cout << a << b; 처럼 연달아 쓸 수 있음)
}

// istream& is는 cin을 가리키는 별명
istream& operator>> (istream& is, String& s) //헤더파일의 istream& operator>> (istream& is, String& s) 부분 범위지정
{
	char str[100];
	is >> str; // cin에게 일단 임시 배열(str)에 입력받으라고 시킴
	s = String(str); // 입력받은 걸로 새 String 객체를 만들어서 s에 덮어씌움
	return is; // cin을 다시 반환
}