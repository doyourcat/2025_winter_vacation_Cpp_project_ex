#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;


class Account
{
private:
    int accId;
    char* cusname;
    int total_money;

public:

    Account(int ID, int money, char* name) : accId(ID), total_money(money)
    {
        cusname = new char[strlen(name) + 1];
        strcpy(cusname, name);
    }

   
    Account(const Account& ref) : accId(ref.accId), total_money(ref.total_money)
    {
        
        cusname = new char[strlen(ref.cusname) + 1];

        strcpy(cusname, ref.cusname);
    }

    int GetAccID() { return accId; }


    void Deposit(int money) {
        total_money += money;
    }


    int Withdraw(int money) {
        if (total_money < money)
            return 0;

        total_money -= money;
        return money;
    }


    void ShowAccInfo() const //멤버 변수의 값을 절대 수정 못함
    {
        cout << "계좌ID: " << accId << endl;
        cout << "이름: " << cusname << endl;
        cout << "잔액: " << total_money << endl;
    }
    ~Account()
    {
        delete[]cusname;
    }
};


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
            acArr[i]->Deposit(money);
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