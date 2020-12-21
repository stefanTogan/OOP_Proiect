#pragma once
#include "CommandParser.h"
#include "CommandExtractor.h"

class ProjectExceptionCommandHandler : exception
{
	string error = "Invalid Index";
public:
	ProjectExceptionCommandHandler() {

	}
	ProjectExceptionCommandHandler(string err) {
		this->error = err;
	}

	string getError() {
		return error;
	}
};
class CommandHandler
{

	int argc_cpy = 0;
	CommandExtractor* ce = nullptr;
public:
	CommandHandler(int argc) : argc_cpy(argc)
	{
	}

	void startHandle(char**& argv_cpy)
	{
		if (this->argc_cpy > 1 && this->argc_cpy < 6)
		{

			for (int i = 0; i < this->argc_cpy - 1; i++)
			{
				string potential = string(argv_cpy[i + 1]);
				this->ce = new CommandExtractor();
				(*ce).readPotentialCommand(potential);
				(*ce).definePotentialCommands();
				for (int j = 0; j < (*ce).getNoCommands(); j++)
				{
					string commandToBeParsed = (*ce).getCommandByIndex(j);
					CommandParser* p1 = new CommandParser(commandToBeParsed);
					(*p1).startParse();
					delete p1;
				}
				delete this->ce;
			}
		}
		else
		{
			throw new  ProjectExceptionCommandHandler();
		}
	}

};
