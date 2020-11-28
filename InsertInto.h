#pragma once
using namespace std;
class ProjectExceptionInsertInto : exception
{

};

class InsertInto {
	string tableName = ""; //Table name
	char** input = nullptr; //Matrix with all words in the input
	int nrWords = 0; //Number of words in the input, matrix

public:

	//constructor
	InsertInto(char** newInput, int newNrWords) {
		this->nrWords = newNrWords - 4;
		this->tableName = string(newInput[0]);
		this->input = new char* [this->nrWords];
		newNrWords = newNrWords - 2;
		int nr = 0;
		for (int i = 2; i < newNrWords; i++) {  //copies matrix of words into class atribute input
			if (_stricmp(newInput[i], "VALUES") != 0) {
				this->input[nr] = new char[strlen(newInput[i]) + 1];
				nr++;
			}
		}
		nr = 0;
		for (int i = 2; i < newNrWords; i++) {
			if (_stricmp(newInput[i], "VALUES") != 0) {
				strcpy(this->input[nr], newInput[i]); 
			}
			nr++;
		}
	}

	InsertInto(const InsertInto& ii) {
		this->tableName = ii.tableName;
		this->nrWords = ii.nrWords;
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
		this->input = new char* [this->nrWords];
		for (int i = 0; i < this->nrWords; i++) {
			this->input[i] = new char[strlen(ii.input[i]) + 1];
		}
		for (int i = 0; i < this->nrWords; i++) {
			strcpy(this->input[i], ii.input[i]);
		}
	}

	~InsertInto() {
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
	}

	void startInsert() {
		if (this->nrWords != 0) {
			this->getInfo();
		}
		else {
			throw new ProjectExceptionInsertInto();
		}
	}

	void getInfo() {
		cout << endl << "The following information is inserted into table " << this->tableName << endl;
		for (int i = 0; i < this->nrWords; i++) {
			cout << this->input[i] << " ";
		}
	}
};
