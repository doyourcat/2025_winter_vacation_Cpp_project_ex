#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20; //매크로상수와 같은 역할

//사용자의 선택 메뉴를 명확하고 깔끔하게 하고자 사용
enum{MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT}; 

//신용등급
enum {LEVEL_A=7, LEVEL_B=4, LEVEL_C=2};

//계좌의 종류
enum{NORMAL=1, CREDIT=2};


//계좌 클래스 선언
class Account {
private:
	int accID;
	int total_money;
	char* cusname;

public:
	Account(int ID, int money, char* name); //기본 생성자

	Account(const Account& ref); //복사 생성자

	int GetAccID() const; //const를 붙임으로 멤버 변수를 안 바뀌게 함
	virtual void Deposit(int money); //나중에 상속받은 클래스에서 입금기능을 다르게 만들 수 있게 함(virtual) = 동적 바인딩
	int Withdraw(int money); 
	void showAccInfo() const; 
	~Account();
};

Account::Account(int ID, int money, char* name) : accID(ID), total_money(money) //이름을 바꿔주기
{
	cusname = new char[strlen(name) + 1];  
	strcpy(cusname, name);
}

Account::Account(const Account& ref) : accID(ref.accID), total_money(ref.total_money) //이름을 복사 생성자로 바꿔주기
{
	cusname = new char[strlen(ref.cusname) + 1];
	strcpy(cusname, ref.cusname);
}

int Account::GetAccID() const { return accID; } 

void Account::Deposit(int money) //총 금액에 입금할 금액 더해주기
{
	total_money += money;
}

int Account::Withdraw(int money) //총 금액에 출금할 금액 빼주기
{
	if (total_money < money)
		return 0;
	total_money -= money;
	return money;
}

void Account::showAccInfo() const //전체 정보 출력
{
	cout << "계좌ID: " << accID << endl;
	cout << "이름: " << cusname << endl;
	cout << "잔액: " << total_money << endl;
}

Account::~Account()
{
	delete[]cusname; //메모리 할당 해제
}

class NormalAccount : public Account //보통 예금계좌 개설_Account 클래스 상속
{
private:
	int interRate; //이자율
public:
	NormalAccount(int ID, int money, char* name, int rate) : Account(ID, money, name), interRate(rate) {}
	virtual void Deposit(int money) //부모 클래스인 Account에서 상속받았으나 가상함수(virtual)를 설정해서 동적 바인딩을 하게 함(서로 다른 내용을 가져야 하므로)
	{
		Account::Deposit(money); //원금 추가
		Account::Deposit(money * (interRate / 100.0)); //이자율 계산하고 추가
	}

};

class HighCreditAccount : public NormalAccount //신용계좌 개설_NormalAccount 클래스 상속
{
private:
	int specialRate;
public:
	HighCreditAccount(int ID, int money, char* name, int rate, int special) : NormalAccount(ID, money, name, rate), specialRate(special)//NomalAccount 클래스 상속
	{ }
	virtual void Deposit(int money)//가상함수(virtual) 설정 해서 동적 바인딩 하게 함(서로 다른 내용 가지기)
	{
		NormalAccount::Deposit(money); //원금과 이자추가
		Account::Deposit(money * (specialRate / 100.0)); //특별이자 계산 후 추가
	}
};

class AccountHandler //계좌 관리 클래스
{
private:
	Account* accArr[100]; //배열 선언
	int accNum;

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

void AccountHandler::ShowMenu(void) const
{
	cout << "====메뉴====" << endl;
	cout << "1) 계좌 생성" << endl;
	cout << "2) 입금" << endl;
	cout << "3) 인출" << endl;
	cout << "4) 전체정보" << endl;
	cout << "5) 종료" << endl;
}

void AccountHandler::MakeAccount(void)
{
	int sel;
	cout << "[계좌종류선택]" << endl;
	cout << "1.보통예금계좌 ";
	cout << "2. 신용신뢰계좌 " << endl;
	cout << "선택: ";
	cin >> sel;

	if (sel == NORMAL) //기존에 선언한 (매크로 상수) NORMAL 변수에 1을 넣고, 사용자의 선택에 따라 if-else로 구분 후 계좌 종류 나눠서 개설
		MakeNormalAccount();
	else
		MakeCreditAccount();
}

void AccountHandler::MakeNormalAccount(void) //MakeNormalAccount 클래스 상속
{
	int id;
	char name[NAME_LEN];
	int total_money;
	int interRate;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌 ID: "; cin >> id;
	cout << "이름: "; cin >> name;
	cout << "입금액: "; cin >> total_money;
	cout << "이자율: "; cin >> interRate;
	cout << endl;

	accArr[accNum++] = new NormalAccount(id, total_money, name, interRate);
}
void AccountHandler::MakeCreditAccount(void) //MakeCreditAccount 클래스 상속
{
	int id;
	char name[NAME_LEN];
	int total_money;
	int interRate;
	int creditLevel; //신용등급 

	cout << "[신용신뢰계좌 개설]" << endl;
	cout << "계좌 ID: "; cin >> id;
	cout << "이름: "; cin >> name;
	cout << "입금액: "; cin >> total_money;
	cout << "이자율: "; cin >> interRate;
	cout << "신용등급(1=A, 2=B, 3=C): "; cin >> creditLevel;
	cout << endl;

	switch (creditLevel)
	{//배열에 동적 메모리 할당한 HighCreditAccount 클래스를 호출하고 사용자에게 입력받은 신용 등급도 저장
	case 1:
		accArr[accNum++] = new HighCreditAccount(id, total_money, name, interRate, LEVEL_A); 
		break;
	case 2:
		accArr[accNum++] = new HighCreditAccount(id, total_money, name, interRate, LEVEL_B);
		break;
	case 3:
		accArr[accNum++] = new HighCreditAccount(id, total_money, name, interRate, LEVEL_C);
	}

}
void AccountHandler::DepositMoney(void)
{
	int money;
	int id;
	cout << "[입금]" << endl;
	cout << "계좌 ID: "; cin >> id;
	cout << "입금액: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id) //저장했던 사용자의 ID를 입금할 때 입력받은 ID와 비교 후 같다면 입력한 금액만큼 입금
		{
			accArr[i]->Deposit(money);
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다. " << endl;
}

void AccountHandler::WithdrawMoney(void)
{
	int money;
	int id;
	cout << "[출금]" << endl;
	cout << "계좌 ID: "; cin >> id;
	cout << "출금액"; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)  //저장했던 사용자의 ID를 출금할 때 입력받은 ID와 비교 후 같다면 입력한 금액만큼 출금
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "잔액부족" <<endl<< endl;
				return;
			}
			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;

}

AccountHandler::AccountHandler():accNum(0) //처음 시작할 때 은행 계좌의 갯수가 0이라고 만들어줌
{ }
void AccountHandler::ShowAllAccInfo(void) const //배열에 저장된 정보를 보여달라고 함
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->showAccInfo();
		cout << endl;
	}
}

AccountHandler::~AccountHandler() //힙 메모리에 만들어서 저장되었던 계좌들 삭제
{
	for(int i = 0; i < accNum; i++)
		delete accArr[i]; //delete 소멸자 사용
}

int main(void)
{
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
			manager.MakeAccount();
			break;
		case 2:
			manager.DepositMoney();
			break;
		case 3:
			manager.WithdrawMoney();
			break;
		case 4:
			manager.ShowAllAccInfo();
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

