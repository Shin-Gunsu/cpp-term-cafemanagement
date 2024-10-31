#include "member.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

ostream& operator<<(ostream& os,const member& m)
{
	cout << "****회원 정보****" << endl;
	os << "이름: " << m.name << endl;
	os << "전화번호: " << m.phone << endl;
	os << "생년월일: " << m.birthDate << endl;
	os << "주소: " << m.address << endl;
	os << "포인트: " << m.point << endl;
	cout << "******************" << endl;
	return os;
}

member::member() : name(""), phone(""), birthDate(0), address(""), point(0.0) {}

member::member(const string& _name,string _password, string _phone, int _birthDate, const string& _address) : name(_name), password(_password), phone(_phone), birthDate(_birthDate), address(_address), point(0) {}

member::member(const string& _name,string _password, string _phone, int _birthDate, const string& _address, double _point) : name(_name),password(_password), phone(_phone), birthDate(_birthDate), address(_address), point(_point) {}

string member::getName() const
{
	return name;
}

string member::getPhone() const
{
	return phone;
}

int member::getBirthDate() const
{
	return birthDate;
}

string member::getPassword() const
{
	return password;
}

string member::getAddress() const
{
	return address;
}

double member::getPoint() const
{
	return point;
}

void member::setName(const string& _name)
{
	name = _name;
}

void member::setPassword(const string& _p)
{
	password = _p;
}

void member::setPhone(string _phone)
{
	phone = _phone;
}

void member::setBirthDate(int _birthDate)
{
	birthDate = _birthDate;
}

void member::setAddress(const string& _address)
{
	address = _address;
}

void member::setPoint(double _point)
{
	point = _point;
}



vector<member> readMembers() {
	vector<member> members;

	ifstream file("member.txt");
	if (!file) {
		cout << "member데이터 베이스 생성..." << endl;
		ofstream createFile("member.txt");
		if (!createFile) {
			cout << "member.txt 파일을 생성할 수 없습니다." << endl;
			return members;
		}
		createFile.close();
		return members;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		member mem;
		ss >> mem.phone;
		ss >> mem.name;
		ss >> mem.password;
		ss >> mem.birthDate;
		ss >> mem.address;
		ss >> mem.point;
		members.push_back(mem);
	}

	file.close();
	return members;
}


void addMember(vector<member>& members) {
	cout << "****************회원 추가****************\n"<<endl;

	// 사용자로부터 회원 정보 입력 받기
	member mem;
	cout << "이름 입력: ";
	cin >> mem.name;
	cout << "비밀번호 입력: ";
	cin >> mem.password;
	cout << "생년월일 입력: ";
	cin >> mem.birthDate;
	cout << "주소 입력: ";
	cin >> mem.address;
	cout << "전화번호 입력: ";
	cin >> mem.phone;


	bool isduple = false;
	for (const auto& m : members) {
		if (m.getPhone() == mem.getPhone()) {
			isduple = true;
		}
	}
	if (isduple) {
		cout << "\n!!이미 가입한 회원입니다!!" << endl;
	}
	else {
		members.push_back(mem);
		cout << "\n****************저장 완료****************\n";
	}
	cout << endl;
}


void deleteMember(vector<member>& members) {
	cout << "\n****************회원 탈퇴****************\n"<<endl;
	string phone;
	cout << "삭제할 회원의 번호를 입력하세요 : ";
	cin >> phone;

	auto it = members.end();
	for (auto iter = members.begin(); iter != members.end(); ++iter) {
		if (iter->getPhone() == phone) {
			it = iter;
			break;
		}
	}
	cout << endl;
	if (it != members.end()) {
		members.erase(it);
		cout << "******회원 정보가 삭제되었습니다.******" << endl;
	}
	else {
		cout << "******해당 정보를 가진 회원이 없습니다.******" << endl;
	}
	cout << endl;
}


void displayMembers(const vector<member>& members) {
	cout << "\n****************회원 목록****************\n";

	for (const auto& mem : members) {
		cout << mem;
		cout << endl;
	}

	cout << "\n*****************************************" << endl;
}

void modifyMember(vector<member>& members) {
	cout << "****************회원 수정****************\n";
	cout << endl;
	// 사용자로부터 수정할 회원의 전화번호 입력 받기
	string phone;
	cout << "수정할 회원의 전화번호 입력: ";
	cin >> phone;

	// 회원 정보 업데이트
	for (auto& mem : members) {
		if (mem.getPhone() == phone) {
			cout << "수정할 회원의 정보를 입력하세요\n";
			string name, address, password;
			int birthDate;

			double point;

			cout << "이름 입력: ";
			cin >> name;
			cout << "생년월일 입력: ";
			cin >> birthDate;
			cout << "주소 입력: ";
			cin >> address;
			cout << "포인트 입력: ";
			cin >> point;
			cout << "비밀번호 입력: ";
			cin >> password;

			mem.setName(name);
			mem.setBirthDate(birthDate);
			mem.setAddress(address);
			mem.setPoint(point);
			mem.setPassword(password);
			cout << "\n****************수정 완료****************\n"<<endl;
			return;
		}
	}
	cout << "******해당 전화번호를 가진 회원이 없습니다******.\n" << endl;
}


void searchMember(const vector<member>& members) {
	cout << "\n****************회원 검색****************\n";
	cout << endl;
	string name;
	cout << "검색할 회원의 이름 입력: ";
	cin >> name;

	bool found = false;

	for (const auto& mem : members) {
		if (mem.getName() == name) {
			cout << mem;
			cout << endl;
			found = true;
		}
	}
	cout << endl;
	if (!found) {
		cout << name << "님은 존재하지 않는 회원 입니다!" << endl;
	}

	cout << "*****************************************\n"<<endl;
}

void saveMembers(const vector<member>& members) {
	ofstream backupFile("member_backup.txt");
	if (!backupFile) {
		cout << "member_backup.txt 파일을 열 수 없습니다." << endl;
		return;
	}

	// 백업 파일에 정보 작성
	for (const auto& mem : members) {
		backupFile << mem.getPhone() << " ";
		backupFile << mem.getName() << " ";
		backupFile << mem.getPassword() << " ";
		backupFile << mem.getBirthDate() << " ";
		backupFile << mem.getAddress() << " ";
		backupFile << mem.getPoint() << endl;
	}

	backupFile.close();

	if (remove("member.txt") != 0) {  // 기존 파일 삭제
		cout << "member.txt 파일을 삭제할 수 없습니다." << endl;
		return;
	}

	if (rename("member_backup.txt", "member.txt") != 0) {  // 변경된 파일이름으로 저장
		cout << "member.txt 파일을 저장할 수 없습니다." << endl;
	}
}


member& login(vector<member>& members) {
	if (members.empty()) {
		static member emptyMember;
		return emptyMember;
	}

	string phone;
	string pw;
	cout << endl;
	cout << "핸드폰 번호를 입력해주세요: ";
	cin >> phone;
	cout << "비밀번호를 입력해 주세요: ";
	cin >> pw;

	for (auto& mem : members) {
		if (mem.getPhone() == phone && mem.getPassword() == pw) {
			return mem;
		}
	}

	static member emptyMember;
	return emptyMember;
}


void buy(vector<menu>& menus,const string& name)
{
	cout << endl;
	bool isExist = false;
	for (auto& item : menus) {
		if (item.getName() == name) {
			item.increaseSales();
			cout <<"******"<< item.getName() << "을" << item.getPrice() << "원에 구입하셨습니다."<<"******" << endl;
			isExist = true;
			break;
		}
	}
	
	if (!isExist) {
		cout << endl;
		cout << "******없는 메뉴입니다.******" << endl;
	}
}

void buy(vector<menu>& menus,const string& name, member& User, vector<member>& mem)
{
	cout << endl;
	bool isExist = false;
	for (auto& item : menus) {
		if (item.getName() == name) {
			double price = item.getPrice();
			User.setPoint(User.getPoint() + price / 100);  // 회원의 포인트 업데이트
			for (member& m : mem) {
				if (m.getPhone() == User.getPhone()) {
					m.setPoint(User.getPoint());  // mem 벡터에서 해당 회원 정보 업데이트
					item.increaseSales();
					cout << item.getName() << "을" << item.getPrice() << "원에 구입하셨습니다." << endl;
					cout << "적립 포인트 :" << item.getPrice() / 100 << endl;
					cout << "현재 포인트 :" << m.getPoint() << endl;
					isExist = true;
					break;				
				}
			}
		}
	}
	cout << endl;
	if (!isExist) {
		cout << "없는 메뉴입니다." << endl;
	}
	cout << "******************************" << endl;
}

