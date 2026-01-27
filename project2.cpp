#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

// 클래스 선언
class Account
{
private:
    int accId;
    char* cusname;
    int total_money;

public:
    // 생성자
    Account(int ID, int money, char* name) : accId(ID), total_money(money)
    {
        cusname = new char[strlen(name) + 1];
        strcpy(cusname, name);
    }

    // 소멸자
    ~Account()
    {
        delete[] cusname;
    }

    int GetAccID() { return accId; }

   
    void Deposit(int money) {
        total_money += money;
    }

    
    int Withdraw(int money) {
        if (total_money < money)
            return 0; // 잔액 부족 시 0 반환

        total_money -= money;
        return money; // 출금 성공 시 출금액 반환
    }

    //정보 출력 함수 : 변수를 출력 스트림에 포함
    void ShowAccInfo()
    {
        cout << "계좌ID: " << accId << endl;
        cout << "이름: " << cusname << endl;
        cout << "잔액: " << total_money << endl;
    }
};

// 객체 포인터 배열로 변경
Account* acArr[100];
int accNum = 0;

void ShowMenu(void);
void Makeaccount(void);
void Inmoney(void);
void Outmoney(void);
void ShowInfo(void);

int main() {
    int choice;

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
            //동적 할당된 객체들을 해제
            for (int i = 0; i < accNum; i++) {
                delete acArr[i];
            }
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

    // new를 사용하면 '주소'가 반환되므로 포인터 배열(Account*)에 저장
    acArr[accNum++] = new Account(id, total_money, name);
}

void Inmoney(void) {
    int money;
    int id;
    cout << "[입금]" << endl;
    cout << "계좌 ID: "; cin >> id;
    cout << "입금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) {
        
        if (acArr[i]->GetAccID() == id)
        {
            acArr[i]->Deposit(money); // 클래스의 입금 함수 호출
            cout << "입금완료" << endl << endl;
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

    for (int i = 0; i < accNum; i++) {
        if (acArr[i]->GetAccID() == id) {

            // 클래스의 출금 함수 호출 (0이면 실패)
            if (acArr[i]->Withdraw(money) == 0) {
                cout << "잔액 부족ㅋ" << endl << endl;
                return;
            }

            cout << "출금완료" << endl << endl;
            return;
        }
    }
    cout << "유효하지 않은 ID 입니다" << endl << endl;
}

void ShowInfo(void) {
    for (int i = 0; i < accNum; i++) {
        acArr[i]->ShowAccInfo();
        cout << endl;
    } 
}