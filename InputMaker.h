#pragma once
#include <string>
using namespace std;

class InputMaker
{
	string material = "";
	char** final = nullptr;
	char* initial = nullptr;
public:
	InputMaker(string material, int sizeLimit)
	{
		this->material = material;
		this->final = new char* [20];
		for (int i = 0; i < 20; i++)
			this->final[i] = new char[sizeLimit]; 

		this->initial = new char[sizeLimit];
	}

	~InputMaker() {
		for (int i = 0; i < 20; i++)
			delete[] this->final[i];
		delete[] final;

		delete[] initial;
	}

	int determineNrWords()
	{
		int number = 0;
		strcpy(this->initial, this->material.c_str());       //makes matrix of words
		char* p;
		p = strtok(this->initial, " (),=");
		while (p != NULL)
		{
			number++;
			p = strtok(NULL, " (),=");
		}
		return number;
	}

	char** transform()
	{
		int number = 0;
		strcpy(this->initial, this->material.c_str());   //makes matrix of words
		char* p;
		p = strtok(this->initial, " (),=");
		while (p != NULL)
		{
			strcpy(this->final[number], p);
			number++;
			p = strtok(NULL, " (),=");
		}

		return this->final;
	}
	
	char** adjust(char** cuv, int nrOfCuv)
	{
		char** adjusted;
		adjusted = new char* [nrOfCuv];  //copies matrix of words into class atribute input
		for (int i = 0; i < nrOfCuv; i++) {
			adjusted[i] = new char[strlen(cuv[i]) + 1];
		}
		for (int i = 0; i < nrOfCuv; i++) {
			strcpy(adjusted[i], cuv[i]);
		}

		return adjusted;
	}
	void displayFinal() 
	{
		if (final != nullptr) {
			for (int i = 0; i < this->determineNrWords(); i++) {
				cout << this->final[i] << endl;
			}
		}
	}
};

