#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

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
	virtual void Deposit(int money); //나중에 상속받은 클래스에서 입금기능을 다르게 만들 수 있게 함(virtual)
	int Withdraw(int money); 
	void showAccInfo() const; 
	~Account();
};

Account::Account(int ID, int money, char* name) : accID(ID), total_money(money) //바꿔주기
{
	cusname = new char[strlen(name) + 1];
	strcpy(cusname, name);
}

Account::Account(const Account& ref) : accID(ref.accID), total_money(ref.total_money)
{
	cusname = new char[strlen(ref.cusname) + 1];
	strcpy(cusname, ref.cusname);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)
{
	total_money += money;
}

int Account::Withdraw(int money)
{
	if (total_money < money)
		return 0;
	total_money -= money;
	return money;
}

void Account::showAccInfo() const
{
	cout << "계좌ID: " << accID << endl;
	cout << "이름: " << cusname << endl;
	cout << "잔액: " << total_money << endl;
}

Account::~Account()
{
	delete[]cusname;
}

class NormalAccount : public Account
{
private:
	int interRate;
public:
	NormalAccount(int ID, int money, char* name, int rate) : Account(ID, money, name), interRate(rate) {}
	virtual void Deposit(int money)
	{
		Account::Deposit(money); //원금 추가
		Account::Deposit(money * (interRate / 100.0)); //이자 추가
	}

};

class HighCreditAccount : public NormalAccount
{
private:
	int specialRate;
public:
	HighCreditAccount(int ID, int money, char* name, int rate, int special) : NormalAccount(ID, money, name, rate), specialRate(special)
	{ }
	virtual void Deposit(int money)
	{
		NormalAccount::Deposit(money); //원금과 이자추가
		Account::Deposit(money * (specialRate / 100.0)); //특별이자 추가
	}
};

class AccountHandler
{
private:
	Account* accArr[100];
	int accNum;

public:
	AccountHandler();
	void ShowMenu(void) const;
	void MakeAccount(void);
	void DepositMoney(void);
	void WithdrawMoney(void);
	void ShowAllAccInfo(void) const;
	~AccountHandler();

protected:
	void MakeNormalAccount(void);
	void MakeCreditAccount(void);
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

	if (sel == NORMAL)
		MakeNormalAccount();
	else
		MakeCreditAccount();
}

void AccountHandler::MakeNormalAccount(void)
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
void AccountHandler::MakeCreditAccount(void)
{
	int id;
	char name[NAME_LEN];
	int total_money;
	int interRate;
	int creditLevel;

	cout << "[신용신뢰계좌 개설]" << endl;
	cout << "계좌 ID: "; cin >> id;
	cout << "이름: "; cin >> name;
	cout << "입금액: "; cin >> total_money;
	cout << "이자율: "; cin >> interRate;
	cout << "신용등급(1toA, 2toB, 3toC): "; cin >> creditLevel;
	cout << endl;

	switch (creditLevel)
	{
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
		if (accArr[i]->GetAccID() == id)
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
		if (accArr[i]->GetAccID() == id)
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

AccountHandler::AccountHandler():accNum(0)
{ }
void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->showAccInfo();
		cout << endl;
	}
}

AccountHandler::~AccountHandler()
{
	for(int i = 0; i < accNum; i++)
		delete accArr[i];
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

