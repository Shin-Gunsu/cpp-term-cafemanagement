#include "menu.h"

using namespace std;

menu::menu() {
	name = "";
	price = 0;
	exp = "";
	sales = 0;
	tag = "";
	cost = 0;
}

menu::menu(const string& _name, int _price,const string& _exp,const string& _tag,int _cost) {
	name = _name;
	price = _price;
	exp = _exp;
	tag = _tag;
	sales = 0;
	cost = _cost;
}

void menu::setName(const string& _name) {
	name = _name;
}

void menu::setExp(const string& _exp) {
	exp = _exp;
}

void menu::setTag(const string& _tag)
{
	tag = _tag;
}

void menu::setCost(int _cost)
{
	cost = _cost;
}

void menu::setPrice(int _price) {
	price = _price;
}

void menu::setSales(int _sales) {
	sales = _sales;
}

string menu::getName() const {
	return name;
}

string menu::getTag() const
{
	return tag;
}

int menu::getPrice() const {
	return price;
}

string menu::getExp() const {
	return exp;
}

int menu::getSales() const {
	return sales;
}
int menu::getCost() const
{
	return cost;
}
void menu::increaseSales() {
	sales++;
}
ostream& operator<<(ostream& os, const menu& c) {
	os << "이름: " << c.name << endl;
	os << "종류: " << c.tag << endl;
	os << "가격: " << c.price << endl;
	os << "설명: " << c.exp << endl;
	return os;
}

void menu::showInfo() const{
	cout << "이름: " << name << endl;
	cout << "태그: " << tag << endl;
	cout << "설명: " << exp << endl;
	cout << "원가: " << cost << endl;
	cout << "가격: " << price << endl;
	cout << "판매량: " << sales << endl;
	cout << "총 판매 가격: " << (price * sales) << endl;
	cout << "수익: " << ((price-cost) * sales) << endl;
}

vector<menu> readMenus() {
	vector<menu> menus;

	ifstream file("menu.txt");
	if (!file) {
		cout << "menu데이터 베이스 생성..." << endl;
		ofstream createFile("menu.txt");
		if (!createFile) {
			cout << "menu.txt 파일을 생성할 수 없습니다." << endl;
			return menus;
		}
		createFile.close();
		return menus;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		menu me;
		getline(ss, me.name, '_');
		getline(ss, me.tag, '_');
		getline(ss, me.exp,'_');
		string str;
		getline(ss, str, '_');
		me.price = stoi(str);
		getline(ss, str, '_');
		me.sales = stoi(str);
		ss >> me.cost;
		

		menus.push_back(me);
	}

	file.close();
	return menus;
}

void addMenu(vector<menu>& menus) {
	cout << "****************메뉴 추가****************\n";
	
	menu mem;
	cout << "제품명 입력: ";
	getline(cin, mem.name);
	cout << "가격 입력: ";
	cin >> mem.price;
	cout << "원가 입력: ";
	cin >> mem.cost;
	cout << "태그 입력: ";
	cin >> mem.tag;
	cin.ignore();
	cout << "설명 입력: ";
	getline(cin, mem.exp);
	bool isduple = false;
	for (const auto& m : menus) {
		if (m.name == mem.name) {
			isduple = true;
		}
	}
	if (isduple) {
		cout << "!!이미 존재하는 메뉴입니다!!" << endl;
	}
	else {
		menus.push_back(mem);
		cout << "\n****************저장 완료****************\n";
	}
}

void deleteMenu(vector<menu>& menus) {
	cout << "\n****************메뉴 삭제****************\n";
	string name;
	cout << "삭제할 메뉴를 입력하세요: ";
	getline(cin, name);

	auto it = menus.end();
	for (auto iter = menus.begin(); iter != menus.end(); ++iter) {
		if (iter->getName() == name) {
			it = iter;
			break;
		}
	}

	if (it != menus.end()) {
		menus.erase(it);
		cout << "메뉴가 삭제되었습니다." << endl;
	}
	else {
		cout << "해당 메뉴가 없습니다." << endl;
	}
}

void displayMenus(const vector<menu>& menus,char i) {
	cout << "\n***************메뉴****************\n";

	if (i == '1') {
		for (const auto& m : menus) {
			cout << m;
			cout << endl;
		}
	}else{
		for (const auto& m : menus) {
			m.showInfo();
			cout << endl;
		}
	}
	cout << "*****************************************\n";
}

void modifyMenu(vector<menu>& menus) {
	cout << "****************메뉴 수정****************\n";

	
	string name;
	cout << "수정할 메뉴 입력: ";
	getline(cin, name);
	
	
	for (auto& mem : menus) {
		if (mem.getName() == name) {
			cout << "\n****************수정할 메뉴의 정보를 입력하세요****************" << endl;
			string name, exp, tag;
			int price, sales,cost;

			cout << "이름 입력: ";
			getline(cin, name);
			cout << "태그 입력: ";
			cin >> tag;
			cin.ignore();
			cout << "설명 입력: ";
			getline(cin, exp);
			cout << "가격 입력: ";
			cin >> price;
			cout << "원가 입력: ";
			cin >> cost;
			cout << "판매량 입력: ";
			cin >> sales;

			mem.setName(name);
			mem.setTag(tag);
			mem.setExp(exp);
			mem.setPrice(price);
			mem.setSales(sales);
			mem.setCost(cost);
			cout << "\n****************수정 완료****************\n";
			return;
		}
	}
	cout << "해당 메뉴가 없습니다." << endl;
}

void showRevenue(const vector<menu>& menus)
{
	menu bestSeller, mostProfit;
	long revenue=0, profit=0;
	for (const auto& mem : menus) {
		if (bestSeller.getSales() < mem.getSales()) {
			bestSeller = mem;
		}
		if ((mostProfit.getCost() * mostProfit.getSales()) < (mem.getCost() * mem.getSales())) {
			mostProfit = mem;
		}
		
		revenue += (mem.getPrice() * mem.getSales());
		profit += ((mem.getPrice()-mem.getCost()) * mem.getSales());
	}
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << endl;
	cout << "총 수익: " << revenue << endl;
	cout << endl;
	cout << "이익   : " << profit << endl;
	cout << endl;
	cout << "제일 많이 팔린 메뉴 :" << bestSeller.getName()<<" "<<bestSeller.getSales()<<"개" << endl;
	cout << endl;
	cout << "수익이 제일 높은 메뉴 :" << mostProfit.getName() <<" "<< (mostProfit.getPrice()-mostProfit.getCost())*mostProfit.getSales()<<"원" << endl;
	cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << endl;
}

void searchMenu(const vector<menu>& menus,char i) {
	cout << "\n****************메뉴 검색****************\n";
	set<string> uniqueTags;
	for (const auto& mem : menus) {
		uniqueTags.insert(mem.getTag());
	}

	cout << "*종류 :";
	for (const auto& tag : uniqueTags) {
		cout <<"<"<< tag << "> ";
	}
	cout << endl << endl;
	string tag;
	cout << "검색할 종류 입력: ";
	cin >> tag;

	cout << endl;
	cout << "*****************************************\n";
	for (const auto& mem : menus) {
		if (mem.getTag() == tag) {
			if (i == '1') {
				cout << mem;
			}
			else {
				mem.showInfo();
			}
			cout << endl;
		}
	}
	cout << endl;
	cout << "*****************************************\n";
}

void saveMenus(const vector<menu>& menus) {
	ofstream backupFile("menu_backup.txt");
	if (!backupFile) {
		cout << "menu_backup.txt 파일을 열 수 없습니다." << endl;
		return;
	}

	// 백업 파일에 정보 작성
	for (const auto& mem : menus) {
		backupFile << mem.getName() << "_";
		backupFile << mem.getTag() << "_";
		backupFile << mem.getExp() << "_";
		backupFile << mem.getPrice() << "_";
		backupFile << mem.getSales() << "_";
		backupFile << mem.getCost() <<endl;
	}

	backupFile.close();

	if (remove("menu.txt") != 0) {  // 기존 파일 삭제
		cout << "menu.txt 파일을 삭제할 수 없습니다." << endl;
		return;
	}

	if (rename("menu_backup.txt", "menu.txt") != 0) {  // 변경된 파일이름으로 저장
		cout << "menu.txt 파일을 저장할 수 없습니다." << endl;
	}
}

