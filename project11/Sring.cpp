#define _CRT_SECURE_NO_WARNINGS
#include "String.h"


//아무것도 없는 빈 String 객체를 만들 때 호출
String::String()
{
	len = 0; //길이
	str = NULL; //포인터는 아무것도 안 가리킴
}


//String 객체로 변환할 때 호출
String::String(const char* s)
{
	len = strlen(s) + 1; // 문자열 길이에 널 문자('\0') 공간 1을 더함
	str = new char[len]; // 필요한 만큼 힙(Heap) 메모리 동적 할당
	strcpy(str, s); // 할당받은 빈 공간에 문자열 내용 복사
}



//기존의 String 객체를 이용해 새로운 객체를 생성할 때 호출
String::String(const String& s)
{
	len = s.len; //원본 객체 길이 그대로
	str = new char[len]; // 원본과 동일한 크기의 새로운 메모리를 힙에 할당
	strcpy(str, s.str); // 원본의 문자열 내용을 새로운 메모리에 복사
}


//객체의 수명이 끝나서 메모리에서 사라질 때 자동으로 호출
String::~String()
{
	if (str != NULL) //포인터가 메모리를 가리킨다면
		delete[]str; //메모리 해제
}


//이미 존재하는 객체에 다른 객체의 값을 덮어쓸 때 호출
String& String::operator= (const String& s)
{
	if (str != NULL)
		delete[]str; //기존에 가지고 있던 메모리를 먼저 지움
	len = s.len; //새로운 길이 대입
	str = new char[len]; //새로운 크기만큼 메모리 다시 할당
	strcpy(str, s.str);  //내용 복사
	return *this; //연산이 끝난 나 자신(객체)을 참조로 반환
}


//내 문자열 뒤에 다른 문자열을 이어 붙임
String& String::operator+= (const String& s)
{
	len += (s.len - 1); //두 문자열 길이를 더함
	char* tempstr = new char[len]; // 두 문자열이 모두 들어갈 수 있는 더 큰 임시 배열 할당
	strcpy(tempstr, str); //임시 배열에 원래 문자열을 이어붙임
	strcat(tempstr, s.str); //그 뒤에 s.str 붙이기

	if (str != NULL)
		delete[]str; //메모리 해제
	str = tempstr;// 내 포인터가 새롭게 만든 곳(임시 배열)을 가리키도록 연결
	return *this; 
}


//두 String 객체의 문자열 내용이 똑같은지 검사
bool String::operator== (const String& s)
{

	// strcmp는 같으면 0, 다르면 0이 아닌 값을 반환함.
	// 0(false)이 나오면 진짜로 같다는 뜻이므로 true를 반환하고, 아니면 false를 반환하도록 삼항 연산자로 논리 뒤집기
	return strcmp(str, s.str) ? false : true;
}



//두 객체는 가만히 두고, 둘을 합쳐서 새로운 제3의 객체를 만들어 반환함
String String::operator+ (const String& s)
{
	char* tempstr = new char[len + s.len - 1]; //임시 배열 동적 할당
	strcpy(tempstr, str);
	strcat(tempstr, s.str);

	String temp(tempstr);
	delete[]tempstr;
	return temp;
}


//cout << s; 를 사용할 수 있게 해줌.
// cout(os)에게 String 내부에 숨겨진 진짜 문자열(s.str)을 출력하라고 지시
ostream& operator<< (ostream& os, const String& s)
{
	os << s.str;
	return os;
}


//cin >> s; 를 사용할 수 있게 해줌
istream& operator>> (istream& is, String& s)
{
	char str[100]; // 입력을 임시로 받을 넉넉한 버퍼 크기의 배열 준비
	is >> str;     // 키보드 입력(cin)을 임시 배열에 저장
	s = String(str);  // 저장된 문자열로 새로운 String 객체를 생성해 s에 대입
	return is;
}