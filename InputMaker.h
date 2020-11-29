#pragma once
#include <string>
using namespace std;

class InputMaker
{
	string material = "";
	char** final = nullptr;
	char* initial = nullptr;
public:
	InputMaker() 
	{
		this->final = new char* [20];
		for (int i = 0; i < 20; i++)
			this->final[i] = new char[2];

		this->initial = new char[2];

	}

	InputMaker(const InputMaker& im)
	{
		this->final = new char* [20];
		for (int i = 0; i < 20; i++)
			this->final[i] = new char[2];

		this->initial = new char[2];
		this->material = im.material;
	}
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

	string getMaterial()
	{
		return this->material;
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

	bool operator==(const InputMaker& im)
	{
		if (this->material.compare(im.material.c_str()) != 0)
			return 0;
		
		return 1;
	}
	InputMaker operator+(string toAdd)
	{
		InputMaker result = *this;
		result.material += toAdd;

		return result;
	}

	void operator++()
	{
		this->material += " ";
		this->material += this->material;
	}

	InputMaker operator!()
	{
		
		InputMaker result = *this;
		for (std::string::size_type i = 0; i < result.material.length(); ++i)
			 result.material[i] = toupper(result.material[i]);

		return result;
	}

	InputMaker operator++(int d)
	{
		InputMaker result = *this;
		result.material += " ";
		result.material += result.material;
		return result;
	}

	char operator[](int i)
	{
		if (i < this->material.size())
			return this->material[i];
		else
			cout << "Invalid input";
	}

	operator string() const
	{
		return this->material;
	}


	InputMaker operator=(const InputMaker& im)
	{
		this->material = im.material;

		return *this;
	}

	friend istream& operator>>(istream& stream,InputMaker& im)
	{
		cout << endl << "Introduce Command:";
		string intermediar;
		stream >> intermediar;
		im.material = intermediar;
		return stream;
	}
};

void operator<<(ostream& stream, InputMaker& im)
{
	stream << im.getMaterial();
}
