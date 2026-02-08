#include "BankingCommonDecl.h"
#include "AccountHandler.h"



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

