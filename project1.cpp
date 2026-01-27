#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> // strcpy 사용을 위함

using namespace std; 

typedef struct { //뒤에 나올 class 대체하는 구조체 선언
    int accId; //개인 아이디용
    char cusname[20]; //개인 이름용
    int total_money; //총 금액 출력용
} Account;

Account acArr[100]; //배열에 저장
int accNum = 0; //저장된 계좌 수

void ShowMenu(void); //메뉴를 보여주는 함수
void Makeaccount(void); //계좌를 만들게 하는 함수
void Inmoney(void); //입금을 하게 하는 함수
void Outmoney(void); //출금을 하게 하는 함수
void ShowInfo(void); //저장된 모든 정보를 출력하는 함수

int main() {
    int choice; //switch-case 문을 활용해 choice 변수에 들어오는 메뉴 숫자에 따라 다른 역할을 하는 함수 호출

    while (1) {
        ShowMenu();
        cout << "선택: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            Makeaccount();
            break;
        case 2:
            Inmoney();
            break;
        case 3:
            Outmoney();
            break;
        case 4:
            ShowInfo();
            break;
        case 5:
            return 0;
        default:
            cout << "부적절한 접근" << endl;
        }
    }
    return 0;
}

void ShowMenu(void) {
    cout << "====메뉴====" << endl;
    cout << "1) 계좌 생성" << endl;
    cout << "2) 입금" << endl;
    cout << "3) 인출" << endl;
    cout << "4) 전체정보" << endl;
    cout << "5) 종료" << endl;
}

void Makeaccount(void) {
    int id;
    char name[20];
    int total_money;

    cout << "[계좌 개설]" << endl;
    cout << "계좌 ID: "; cin >> id;
    cout << "이름: "; cin >> name;
    cout << "입금액: "; cin >> total_money;

    acArr[accNum].accId = id; //배열의 구조체 accId에 입력받은 id값 저장
    acArr[accNum].total_money = total_money; //배열의 구조체 total_money에 입력받은 toal_money값 저장
    strcpy(acArr[accNum].cusname, name); //배열의 구조체 cusname에 입력받은 name값 저장

    accNum++; //계좌를 생성했기에 기존 계좌 수에서 증가
    cout << "계좌 생성 완료\n" << endl;
}

void Inmoney(void) {
    int money;
    int id;
    cout << "[입금]" << endl;
    cout << "계좌 ID: "; cin >> id;
    cout << "입금액: "; cin >> money;

    
    for (int i = 0; i < accNum; i++) { //accNum에 저장된 계좌 수와 지역변수 i와 비교 후 계좌 정보가 저장되어있는 배열을 찾음
        if (acArr[i].accId == id) {
            acArr[i].total_money += money; //계좌에 있던 기존의 total_money에 입력받은 money 값을 더해줌
            cout << "입금 완료" << endl << endl;
            return; 
        }
    }
   
    cout << "유효하지 않은 ID 입니다" << endl << endl;
}

void Outmoney(void) {
    int money;
    int id;
    cout << "[출금]" << endl;
    cout << "계좌 ID: "; cin >> id;
    cout << "출금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) { //accNum에 저장된 계좌 수와 지역변수 i와 비교 후 계좌 정보가 저장되어있는 배열을 찾음
        if (acArr[i].accId == id) {
            
            if (acArr[i].total_money < money) { //계좌에 있던 기존의 total_money에 저장된 값이 입력한 money 값보다 작으면 잔액 부족을 화면출력
                cout << "잔액 부족ㅋ" << endl << endl;
                return;
            }
            acArr[i].total_money -= money; ////계좌에 있던 기존의 total_money에 입력받은 money 값을 빼줌
            cout << "출금완료" << endl << endl;
            return;
        }
    }
    cout << "유효하지 않은 ID 입니다" << endl << endl;
}

void ShowInfo(void) {
    
    for (int i = 0; i < accNum; i++) { //accNum에 저장된 계좌 수와 지역변수 i와 비교 후 계좌 정보가 저장되어있는 배열을 찾음
        cout << "계좌ID: " << acArr[i].accId << endl; //각 배열의 구조체에 해당되는 배열들을 가져와 사용자에게 모든 정보를 화면 출력
        cout << "이름: " << acArr[i].cusname << endl;
        cout << "잔액: " << acArr[i].total_money << endl << endl;
    }
}