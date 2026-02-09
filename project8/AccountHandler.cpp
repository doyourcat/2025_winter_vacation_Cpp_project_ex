#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"


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
				cout << "잔액부족" << endl << endl;
				return;
			}
			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;

}

AccountHandler::AccountHandler() :accNum(0) //처음 시작할 때 은행 계좌의 갯수가 0이라고 만들어줌
{
}
void AccountHandler::ShowAllAccInfo(void) const //배열에 저장된 정보를 보여달라고 함
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		cout << endl;
	}
}

AccountHandler::~AccountHandler() //힙 메모리에 만들어서 저장되었던 계좌들 삭제
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i]; //delete 소멸자 사용
}
