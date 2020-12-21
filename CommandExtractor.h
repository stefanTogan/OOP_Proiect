#pragma once
using namespace std;

class ProjectExceptionCommandExtractor : exception
{
	string error = "Invalid Index";
public:
	ProjectExceptionCommandExtractor() {

	}
	ProjectExceptionCommandExtractor(string err) {
		this->error = err;
	}

	string getError() {
		return error;
	}
};

class CommandExtractor
{
	vector<string> readCommands;
	int noCommands = 0;
    vector<string> possibleCommands = { "CREATE", "SELECT", "DROP", "DISPLAY", "DELETE", "UPDATE" };
	int index = 0;
public: 
	CommandExtractor() = default;
	void write2File(ofstream& file)
	{
	}

	void readPotentialCommand(string fileName)
	{
		ifstream inputFile(fileName, ios::in);
		if (inputFile.is_open())
		{
			while (!inputFile.eof())
			{
				string line;
				while (getline(inputFile, line))
				{
					if (line.size() > 1)
					   readCommands.push_back(line);
				}

			}
		}
		else
		{
			cout << "the file is not opened";
		}
	}

	void definePotentialCommands()
	{
		for (int i = 0; i < readCommands.size(); i++)
		{
			int ok = 0;
			string first = this->firstWordExtractor(this->readCommands[i]);
			for (int j = 0; j < this->possibleCommands.size(); j++)
			{
				string p = this->possibleCommands[j];
				transform(first.begin(), first.end(), first.begin(), ::toupper);
				if (!p.compare(first))
					ok = 1;
			}
			if (!ok && i > 0)
			{
				string p = " " + readCommands[i];
				readCommands[i - 1] += p;
				readCommands.erase(readCommands.begin() + i);
			}
		}
	}

	string getCommandByIndex(int j)
	{
		if (j >= this->getNoCommands())
			throw new ProjectExceptionCommandExtractor();
		else
		{
			return this->readCommands[j];
		}
	}

	int getNoCommands()
	{
		return this->readCommands.size();
	}

	void displayCommands()
	{
		for (int i = 0; i < this->getNoCommands(); i++)
		{
			cout << endl << this->readCommands[i];
		}
	}

	string firstWordExtractor(string sentence)
	{
		string firstWord = sentence.substr(0, sentence.find(" "));
		return firstWord;
	}

	
};
