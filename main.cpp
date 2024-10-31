#include<iostream>
#include<vector>
#include"member.h"
#include"menu.h"
int main() {
	char userSelect;
	vector<member> mem = readMembers();
	vector<menu> men = readMenus();
	member User;

	cout << "-------------------------------------------------------" << endl;
	cout << endl;
	cout << "                   카페 관리 프로그램                  " << endl;
	cout << endl;
	cout << "-------------------------------------------------------" << endl;

	cout << "고객/관리자중 선택하세요" << endl;
	cout << "1. 고객" << endl;
	cout << "2. 관리자" << endl;
	cin >> userSelect;
	if (userSelect == '1') {
		int log;
		
		bool success=false;
		cout << "안녕하세요 고객님, 멤버쉽 로그인 하시겠습니까?" << endl;
		cout << "1. 예" << endl;
		cout << "2.아니요" << endl;
		cin >> log;
		if (log == 1) {
			User = login(mem);
			if (User.getPhone() == "") {
				cout << "로그인에 실패하였습니다" << endl;
			}
			else {
				cout << "로그인 성공하였습니다" << endl;
				success = true;
			}
		}
		else if(log==2){
			cout << "비회원으로 진행합니다" << endl;
		}
		else {
			cout << "잘못된 입력" << endl;
			return 0;
		}
		while (1) {
			cout << endl;
			cout << "********************************" << endl;
			cout << "옵션을 선택하세요." << endl;

			cout << "<1. 메뉴 전체 출력> " << " <2. 종류별로 보기> " << " <3. 구입하기> " << " <4.회원 정보보기> " << " <5. 프로그램 종료>" << endl;

			char input;
			cin >> input;
			string name;
			menu item;
			switch (input)
			{
			case '1':displayMenus(men, userSelect);
				break;
			case '2':searchMenu(men, userSelect);
				break;
			case '3':
				cin.ignore();
				cout << "구매할 메뉴를 입력하세요 : ";
				getline(cin, name);
				if (success) {
					buy(men,name, User, mem);
					saveMembers(mem);
				}
				else {
					buy(men,name);
					saveMembers(mem);
				}
				saveMenus(men);
				
				break;
			case '4':
				if (success) {
					cout << User << endl;
				}
				else {
					cout << "로그인을 해야합니다" << endl;
				}
				break;
			case '5': cout << "프로그램을 종료하겠습니다." << endl;
				saveMembers(mem);
				return 0;
			default:cout<<"잘못 입력하셨습니다."<<endl;
				cin.clear();
				break;
			}
		}
	}
	else if (userSelect == '2') {
		cout << "어서오세요 관리자님" << endl;
		
		while (1) {
			cout << endl;
			cout << "********************************" << endl;
			cout << "관리자 옵션을 선택하세요" << endl;
			char opt;
			cout << "<1. 메뉴 관리> " << " <2. 회원 관리> " <<" <3. 프로그램 종료>" << endl;
			cin >> opt;
			if (opt == '1') {
				bool loof=true;
				while (loof) {
					cout << endl;
					cout << "********************************" << endl;
					cout << "메뉴 관리 모드입니다." << endl;
					cout << "<1. 전체 메뉴 출력> " << " <2. 종류별로 출력> " << " <3. 메뉴 추가> " << endl << "<4. 메뉴 수정> " << " <5. 메뉴 삭제> "<<" <6. 수익 확인> " << " <7. 메뉴 관리 모드 나가기>" << endl;
					char input;
					cin >> input;

					switch (input)
					{
					case '1':displayMenus(men, userSelect);
						break;
					case '2':searchMenu(men, userSelect);
						break;
					case '3':
						cin.ignore();
						addMenu(men);
						saveMenus(men);
						break;
					case '4':
						cin.ignore();
						modifyMenu(men);
						saveMenus(men);
						break;
					case '5':
						cin.ignore();
						deleteMenu(men);
						saveMenus(men);
						break;
					case'6':
						showRevenue(men);
						break;
					case '7':
						cout << "메뉴 관리모드에서 나갑니다." << endl;
						loof = false;
						break;
					default:
						cout << "잘못 입력하셨습니다." << endl;
						break;
					}
				}
			}
			else if (opt == '2') {
				bool loof = true;
				char input;
				while (loof) {
					cout << endl;
					cout << "********************************" << endl;
					cout << "회원 관리 모드입니다." << endl;
					cout << "<1. 전체 회원 출력> " << " <2. 회원 검색> " << " <3. 회원 추가> "<<endl << "<4. 회원 수정> " << " <5. 회원 삭제> " << " <6. 회원 관리 모드 나가기>" << endl;
					
					cin >> input;

					switch (input)
					{
					case '1':displayMembers(mem);
						break;
					case '2':searchMember(mem);
						break;
					case '3':
						addMember(mem);
						saveMembers(mem);
						break;
					case '4':
						modifyMember(mem);
						saveMembers(mem);
						break;
					case '5':deleteMember(mem);
						saveMembers(mem);
						break;
					case '6':
						cout << "회원 관리모드에서 나갑니다." << endl;
						loof = false;
						break;
					default:
						cout << "잘못 입력하셨습니다." << endl;
						break;
					}
				}
			}
			else if(opt=='3'){
				cout << "프로그램을 종료하겠습니다" << endl;
				return 0;
			}
			else {
				cout << endl;
				cout << "잘못 입력하셨습니다." << endl;
			}
		}
	}
}