#pragma once
#include<string>
#include<vector>
#include"menu.h"
using namespace std;
class member {
private:
	string name;
	string phone;
	int birthDate;
	string password;
	string address;
	double point;
public:
	member();
	member(const string& _name, string _password, string _phone, int _birthDate, const string& _address);
	member(const string& _name, string _password, string _phone, int _birthDate, const string& _address,double _point);
	string getName() const;
	string getPhone() const;
	int getBirthDate() const;
	string getPassword() const;
	string getAddress() const;
	double getPoint()const;
	void setName(const string& _name);
	void setPassword(const string& _p);
	void setPhone(string _phone);
	void setBirthDate(int _birthDate);
	void setAddress(const string& _address);
	void setPoint(double _point);
	friend ostream& operator<<(ostream& os,const member& m);
	friend void addMember(vector<member>& members);
	friend vector<member> readMembers();
};
void addMember(vector<member>& members);
vector<member> readMembers();
void displayMembers(const vector<member>& members);
void deleteMember(vector<member>& members);
void modifyMember(vector<member>& members);
void searchMember(const vector<member>& members);
void saveMembers(const vector<member>& members);
member& login(vector<member>& members);
void buy(vector<menu>& ,const string&);
void buy(vector<menu>& ,const string&,member& m,vector<member>&);