#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

//Account 클래스
// 역할: 데이터를 담고 있음
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

    // 복사 생성자 (깊은 복사)
    Account(const Account& ref) : accId(ref.accId), total_money(ref.total_money)
    {
        cusname = new char[strlen(ref.cusname) + 1];
        strcpy(cusname, ref.cusname);
    }

    // const 추가: 이 함수들은 멤버 변수를 절대 수정하지 않겠다는 약속
    int GetAccID() const { return accId; }

    void Deposit(int money) {
        total_money += money;
    }

    int Withdraw(int money) {
        if (total_money < money)
            return 0;

        total_money -= money;
        return money;
    }

    void ShowAccInfo() const
    {
        cout << "계좌ID: " << accId << endl;
        cout << "이름: " << cusname << endl;
        cout << "잔액: " << total_money << endl;
    }

    ~Account()
    {
        delete[] cusname;
    }
};


// [컨트롤 클래스] AccountHandler
class AccountHandler
{
private:
    //전역 변수였던 배열과 개수 변수가 여기로 숨겨짐 (캡슐화)
    Account* acArr[100]; // 계좌 정보를 저장하는 포인터 배열 (관리자가 직접 관리)
    int accNum;          // 저장된 계좌 수

public:
    // 생성자: 컨트롤 클래스가 만들어질 때 변수 초기화
    AccountHandler() : accNum(0) {}

    // 소멸자: 프로그램 종료 시(관리자 퇴근 시) 힙 메모리 자동 정리
    ~AccountHandler() {
        for (int i = 0; i < accNum; i++) {
            delete acArr[i]; // 각각의 Account 객체 소멸
        }
    }

    // 원래 전역 함수였던 ShowMenu가 관리자의 멤버 함수가 됨
    void ShowMenu(void) const {
        cout << "====메뉴====" << endl;
        cout << "1) 계좌 생성" << endl;
        cout << "2) 입금" << endl;
        cout << "3) 인출" << endl;
        cout << "4) 전체정보" << endl;
        cout << "5) 종료" << endl;
    }

    //Makeaccount도 관리자의 멤버 함수가 됨
    void Makeaccount(void) {
        int id;
        char name[20];
        int total_money;

        cout << "[계좌 개설]" << endl;
        cout << "계좌 ID: "; cin >> id;
        cout << "이름: "; cin >> name;
        cout << "입금액: "; cin >> total_money;

        // acArr와 accNum이 같은 클래스 멤버 변수이므로 바로 사용 가능
        acArr[accNum++] = new Account(id, total_money, name);
        cout << "계좌 생성 완료\n" << endl;
    }

    //Inmoney 함수 이동
    void Inmoney(void) {
        int money;
        int id;
        cout << "[입금]" << endl;
        cout << "계좌 ID: "; cin >> id;
        cout << "입금액: "; cin >> money;

        // accNum에 저장된 계좌 수와 지역변수 i와 비교 후 계좌 정보가 저장되어있는 배열을 찾음
        for (int i = 0; i < accNum; i++) {
            if (acArr[i]->GetAccID() == id)
            {
                //해당 객체에게 돈을 더하라고 시킴
                acArr[i]->Deposit(money);
                cout << "입금완료" << endl << endl;
                return;
            }
        }
        cout << "유효하지 않은 ID 입니다" << endl << endl;
    }

    //  Outmoney 함수 이동
    void Outmoney(void) {
        int money;
        int id;
        cout << "[출금]" << endl;
        cout << "계좌 ID: "; cin >> id;
        cout << "출금액: "; cin >> money;

        // accNum에 저장된 계좌 수와 지역변수 i와 비교 후 계좌 정보가 저장되어있는 배열을 찾음
        for (int i = 0; i < accNum; i++) {
            if (acArr[i]->GetAccID() == id) {

                // 잔액 부족 시 0 반환 체크
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

    //ShowInfo 함수 이동
    void ShowInfo(void) const {
        // 각 배열의 구조체(객체)에 해당되는 배열들을 가져와 사용자에게 모든 정보를 화면 출력
        for (int i = 0; i < accNum; i++) {
            acArr[i]->ShowAccInfo();
            cout << endl;
        }
    }
};


int main() {
    // 컨트롤 클래스(관리자) 객체 생성! 
    // 이제 모든 작업은 이 'manager'를 통해서 진행됨
    AccountHandler manager;
    int choice;

    while (1) {
        // manager에게 메뉴 보여달라고 시킴
        manager.ShowMenu();
        cout << "선택: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            // manager에게 계좌 만들라고 시킴
            manager.Makeaccount();
            break;
        case 2:
            manager.Inmoney();
            break;
        case 3:
            manager.Outmoney();
            break;
        case 4:
            manager.ShowInfo();
            break;
        case 5:
            //  return 0;으로 main이 끝나면
            // 지역 변수인 'manager'가 사라지면서 소멸자가 호출되어 메모리가 자동 정리
            return 0;
        default:
            cout << "부적절한 접근" << endl;
        }
    }
    return 0;
}