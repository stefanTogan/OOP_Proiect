#pragma once
using namespace std;

class ProjectExceptionDropTable : exception
{

};

class DropTable {
	string tableName = "";
public:
	DropTable(string name) {
		this->tableName = name;
	}

	void startDropTable(int nrWords) {
		if (nrWords == 3) {
			this->getInfo();
			Tables::noTables--;
		}
		else {
			throw new ProjectExceptionDropTable();
		}
	}

	void getInfo() {
		cout << endl << "Table with name " << this->tableName << " is dropped";
	}
};