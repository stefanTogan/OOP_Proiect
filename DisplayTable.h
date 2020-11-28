#pragma once
using namespace std;

class ProjectExceptionDisplayTable : exception
{

};

class DisplayTable {
	string name = "";
public:
	DisplayTable(string name) {
		this->name = name;
	}

	void startDisplayTable(int nrWords) {
		if (nrWords == 3) {
			this->getInfo();
		}
		else throw new ProjectExceptionDisplayTable();
	}
	void getInfo() {
		cout <<endl<< "Command displays contents of table " << this->name;
	}

	string getName() {
		return this->name;
	}
};
