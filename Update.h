#pragma once
using namespace std;

class ProjectExceptionUpdate : exception
{

};

//UPDATE table_name SET column_name = value WHERE column_name = value
class Update {
	string tableName = ""; //Table name
	char** input = nullptr; //Matrix with all words in the input
	int nrWords = 0; //Number of words in the input, matrix
	bool structure = true;

public:

	//constructor
	Update(char** newInput, int newNrWords) {
		this->tableName = string(newInput[0]);
		this->nrWords = newNrWords-3;
		this->input = new char* [this->nrWords];
		newNrWords = newNrWords - 1;		
		int nr = 0;
		bool ok = 0;
		for (int i = 2; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "WHERE") != 0) {
				this->input[nr] = new char[strlen(newInput[i]) + 1];
				nr++;
			}
		}
		nr = 0;
		for (int i = 2; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "WHERE") != 0) {
				strcpy(this->input[nr], newInput[i]);
				nr++;
			}
			else {
				ok = 1;
			}
		}
		if (ok == 1) {
			this->nrWords--;
		}
		if (ok == 0) {
			this->structure = false;
		}
		cout << this->nrWords;
		for (int i = 0; i < this->nrWords; i++) {
			cout <<endl<< this->input[i];
		}
	}

	//copy constructor
	Update(const Update& u) {
		this->tableName = u.tableName;
		this->nrWords = u.nrWords;
		this->structure = u.structure;
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
		this->input = new char* [this->nrWords];
		for (int i = 0; i < this->nrWords; i++) {
			this->input[i] = new char[strlen(u.input[i]) + 1];
		}
		for (int i = 0; i < this->nrWords; i++) {
			strcpy(this->input[i], u.input[i]);
		}
	}
	
	//destructor
	~Update() {
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
	}

	void startUpdate() {
		if (this->nrWords >= 2) {
			getInfo();
		}
	}
	void getInfo() {
		if (this->nrWords == 2 && this->structure == false) {
			cout <<endl<< "In table " << this->tableName << " all information on column " << this->input[0] << " is changed to " << this->input[1];
		}
		else
			if (this->nrWords == 4 && this->structure == true) {
			cout<<endl<< "In table " << this->tableName << " all information on column " << this->input[0] << " is changed to " << this->input[1]<<" where information on column "<<this->input[2]<<" = "<<this->input[3];
			}
			else
				throw new ProjectExceptionUpdate();
	}
};