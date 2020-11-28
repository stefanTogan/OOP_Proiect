#pragma once
using namespace std;

class ProjectExceptionSelect : exception
{

};
//SELECT(at_least_one_column, ...) | ALL FROM table_name[WHERE column_name = value]
class Select {
	string tableName = ""; //Table name
	int nrConditions = 0; //Number of conditons in the input, matrix
	char** conditions = nullptr; //Matrix with all words in the input
	int nrColumns = 0;  //number of columns to select
	char columns[20][200];  //columns to select
	bool formatType = 0; //=0 if there is no WHERE, 1 otherwise

public:
	//constructor
	Select() {

	}

	//copy constructor
	Select(const Select& s) {
		this->tableName = s.tableName;
		this->nrConditions = s.nrConditions;
		this->nrColumns = s.nrColumns;
		this->formatType = s.formatType;
		if (this->conditions != nullptr) {
			for (int i = 0; i < this->nrConditions; i++)
				delete[] this->conditions[i];
			delete[] this->conditions;
		}
		this->conditions = new char* [this->nrConditions];
		for (int i = 0; i < this->nrConditions; i++) {
			this->conditions[i] = new char[strlen(s.conditions[i]) + 1];
		}
		for (int i = 0; i < nrColumns; i++) {
			strcpy(this->columns[i], s.columns[i]);
		}
	}
	
	//destructor
	~Select() {
		if (this->conditions != nullptr) {
			for (int i = 0; i < this->nrConditions; i++)
				delete[] this->conditions[i];
			delete[] this->conditions;
		}
	}

	void addInformation(char** newInput, int newNrWords) {
		if (_stricmp(newInput[0], "ALL") == 0 && _stricmp(newInput[1], "FROM") != 0)
		{
			throw new ProjectExceptionSelect();
		}
		//in columns stores all columns to be selected
		if (_stricmp(newInput[0], "ALL") == 0) {
			this->nrColumns = 1;
			strcpy(this->columns[0], newInput[0]);
		}
		else {
			this->nrColumns = 0;
			for (int i = 0; i < newNrWords && (_stricmp(newInput[i], "FROM") != 0); i++) {
				strcpy(this->columns[this->nrColumns], newInput[i]);
				this->nrColumns++;
			}
		}
		if (this->formatType == 1) {
			int i;
			for (i = 0; i < newNrWords && (_stricmp(newInput[i], "WHERE") != 0); i++){}
			this->nrConditions = 0;
			this->conditions = new char* [newNrWords - i];
			for (++i; i < newNrWords; i++) {
				this->conditions[this->nrConditions] = new char[strlen(newInput[i]) + 1];
				strcpy(this->conditions[this->nrConditions], newInput[i]);
				this->nrConditions++;
			}
		}
	}

	void startSelect() {
		this->getInfo();
	}

	void getInfo() {
		if (formatType == 0) {
			cout << endl << "Selects ";
			for (int i = 0; i < this->nrColumns; i++) {
				cout << columns[i] << " ";
			}
			cout << "columns from table " << this->tableName;
		}
		else {
			if (this->nrConditions != 2) {
				throw new ProjectExceptionSelect();
			}
			cout << endl << "Selects ";
			for (int i = 0; i < this->nrColumns; i++) {
				cout << columns[i] << " ";
			}
			cout << "columns from table " << this->tableName<<" where "<<this->conditions[0]<< " = "<<this->conditions[1];
		}
	}

	bool checkFormat(char** newInput, int newNrWords) {
		bool ok = false;
		int pozFrom = -1;
		for (int i = 0; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "FROM") == 0) {
				ok = true;
				pozFrom = i;
			}
		}
		if (ok == false) {
			throw new ProjectExceptionSelect();
		}
		int pozWhere = -1;
		for (int i = 0; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "WHERE") == 0) {
				formatType = 1;
				pozWhere = i;
			}
		}
		if (formatType == 1 && pozWhere - pozFrom != 2) {
			throw new ProjectExceptionSelect();
		}
		setTableName(string(newInput[pozFrom + 1]));
	}

	void setTableName(string name) {
		this->tableName = name;
	}
};