#pragma once

#ifndef __BOUND_CHECK_ARRAY_H__
#define __BOUND_CHECK_ARRAY_H__

#include "BankingCommonDecl.h"

template <typename T>
class BoundCheckArray
{
private:
	T* arr; //실제 데이터가 저장될 동적 배열의 시작 주소(템플릿 변수로 받음)
	int arrlen;//배열의 최대 칸 기억하는 역할(나중에 범위를 벗어났는지 확인하는 데에 기준으로 쓰임)

	//BoundCheckArray는 생성자에서 new Y[len]을 통해 힙 메모리를 빌려쓰는 클래스이기 때문에 외부에서 이 배열을 통째로 복사하려할 때에 복사를 못하게 막는 역할
	//외부에서 복사하려할 때 컴파일러가 복사생성자(private) 때문에 복사를 못한다는 뜻으로 에러 뜨게 함
	BoundCheckArray(const BoundCheckArray& arr) {} //복사 생성자
	BoundCheckArray& operator=(const BoundCheckArray& arr) {} //대입 연산자

public:
	BoundCheckArray(int len = 100);
	T& operator[] (int idx);
	T operator[] (int idx) const;
	int GetArrLen() const;
	~BoundCheckArray();
};

template <typename T> //template 함수 
BoundCheckArray<T>::BoundCheckArray(int len) :arrlen(len)
{
	arr = new T[len]; //템플릿 변수 타입의 배열을 len 크기만큼 힙 메모리에 생성
}

template <typename T>
T& BoundCheckArray<T>::operator[] (int idx)
{
	if (idx < 0 || idx >= arrlen) //idx가 0보다 작거나 배열 길이보다 크면 경고 후 프로그램 강제 종료
	{
		cout << "Array index out of bound exception" << endl;
		exit(1);
	}
	return arr[idx]; //참조형(템플릿&) 반환->값 수정 가능
}

template <typename T>
T BoundCheckArray<T>::operator[] (int idx) const
{
	if (idx < 0 || idx >= arrlen) 
	{
		cout << "Array index out of bound exception" << endl;
		exit(1);
	}
	return arr[idx]; //참조형(템플릿&) 반환->값 수정 불가능(=데이터 안 바뀜! ㅇㅅㅇ)
}

template <typename T>
int BoundCheckArray<T>::GetArrLen() const
{
	return arrlen;
}

template <typename T>
BoundCheckArray<T>::~BoundCheckArray()
{
	delete[]arr;  //BoundCheckArray<T>::BoundCheckArray(int len) :arrlen(len)에서 사용한 메모리를 해제

}

#endif
