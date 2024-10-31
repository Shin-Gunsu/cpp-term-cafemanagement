#pragma once
#include <string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
using namespace std;
class menu {
private:
	string name;
	string exp;
	string tag;
	int price;
	int sales;
	int cost;
public:
	menu();
	menu(const string& _name, int _price,const string&,const string&,int cost);
	void setName(const string& _name);
	void setPrice(int _price);
	void setSales(int _sales);
	void setExp(const string& _exp);
	void setTag(const string& _tag);
	void setCost(int _cost);
	string getName() const;
	string getTag() const;
	int getPrice() const;
	int getSales() const;
	int getCost() const;
	string getExp() const;
	friend ostream& operator<<(ostream& os, const menu& c);
	friend void addMenu(vector<menu>&);
	friend vector<menu> readMenus();
	void increaseSales();
	void showInfo()const;
};

vector<menu> readMenus();
void displayMenus(const vector<menu>&,char i);
void deleteMenu(vector<menu>&);
void searchMenu(const vector<menu>&,char i);
void saveMenus(const vector<menu>&);
void modifyMenu(vector<menu>& menus);
void showRevenue(const vector<menu>& menus);
