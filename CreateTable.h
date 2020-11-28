#pragma once
#include "Tables.h"
using namespace std;

class ProjectExceptionCreateTable : exception
{
	
};

class CreateTable {
	char** input = nullptr; //Matrix with all words in the input
	int nrWords = 0; //Number of words in the input, matrix
	vector <string> dataTypes = { "text","int","float","date" }; //all acceptable data types for columns

public:

	//constructor
	CreateTable(char** newInput, int newNrWords) {  //receives matrix of words and nr of words
		this->nrWords = newNrWords - 2;
		this->input = new char* [this->nrWords];
		for (int i = 0; i < this->nrWords; i++) {  //copies matrix of words into class atribute input
			this->input[i] = new char[strlen(newInput[i]) + 1];
		}
		for (int i = 0; i < this->nrWords; i++) {
			strcpy(this->input[i], newInput[i]);
		}
	}

	//copy constructor
	CreateTable(const CreateTable& ct) {
		this->nrWords = ct.nrWords;
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
		this->input = new char* [this->nrWords];
		for (int i = 0; i < this->nrWords; i++) {
			this->input[i] = new char[strlen(ct.input[i]) + 1];
		}
		for (int i = 0; i < this->nrWords; i++) {
			strcpy(this->input[i], ct.input[i]);
		}
	}

	//the destroyer
	~CreateTable() {
		if (this->input != nullptr) {
			for (int i = 0; i < this->nrWords; i++)
				delete[] this->input[i];
			delete[] this->input;
		}
	}


	//creates the new table with given info
	void startCreate() {
		//checks if we have at least 1 column and if each column has a data type
		if (this->nrWords >= 3 && this->nrWords % 2 == 1) {
			//check data type of columns
			for (int i = 2; i < this->nrWords; i = i + 2) {
				int ok = 0;
				for (int j = 0; j < dataTypes.size(); j++) {
					if (_stricmp(this->input[i], dataTypes[j].c_str())==0) {
						ok = 1;
					}
				}
				if (ok == 0) {
					throw new ProjectExceptionCreateTable();
				}
			}
			this->getInfo();
			Tables table(this->input,this->nrWords);
		}
		else
		{
			throw new ProjectExceptionCreateTable();
		}
	}

	void getInfo() {
		cout << endl << "Created table with name: " << this->input[0];
		cout << endl << "Table columns and data types:" << endl;
		for (int i = 1; i < nrWords; i=i+2) {
			cout << this->input[i] << " " << this->input[i+1] << endl;
		}
	}

	//operators
	CreateTable operator=(const CreateTable& ct) {
		if (this != &ct) {
			this->nrWords = ct.nrWords;
			if (this->input != nullptr) {
				for (int i = 0; i < this->nrWords; i++)
					delete[] this->input[i];
				delete[] this->input;
			}
			this->input = new char* [this->nrWords];
			for (int i = 0; i < this->nrWords; i++) {
				this->input[i] = new char[strlen(ct.input[i]) + 1];
			}
			for (int i = 0; i < this->nrWords; i++) {
				strcpy(this->input[i], ct.input[i]);
			}
		}
		return *this;
	}
};

