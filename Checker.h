#pragma once
#include "CommandParser.h"

class ProjectExceptionChecker : exception
{
    string error = "Invalid input";
public:
    ProjectExceptionChecker() {

    }
    ProjectExceptionChecker(string err) {
        this->error = err;
    }

    string getError() {
        return error;
    }
};


class Checker
{

public:
	bool checkLenght(char** inputToCheck, int sizeToCheck)
	{
        if (sizeToCheck == 0) {
            throw new ProjectExceptionChecker("Empty command received");
            return 0;
        }
        else
            if (sizeToCheck <= 2) {
                throw new ProjectExceptionChecker("Too few arguments");
                return 0;
            }
            else
                if (sizeToCheck < 4) {
                    if ((_stricmp(inputToCheck[0], "CREATE") == 0) && (_stricmp(inputToCheck[1], "INDEX") == 0)) {
                        throw new ProjectExceptionChecker("Too few arguments");
                        return 0;
                    }
                    if ((_stricmp(inputToCheck[0], "INSERT") == 0) && (_stricmp(inputToCheck[1], "INTO") == 0)) {
                        throw new ProjectExceptionChecker("Too few arguments");
                        return 0;
                    }
                    if ((_stricmp(inputToCheck[0], "DELETE") == 0) && (_stricmp(inputToCheck[1], "FROM") == 0)) {
                        throw new ProjectExceptionChecker("Too few arguments");
                        return 0;
                    }
                    if ((_stricmp(inputToCheck[0], "UPDATE") == 0)) {
                        throw new ProjectExceptionChecker("Too few arguments");
                        return 0;
                    }
                }
                else
                    if (sizeToCheck < 5) {
                        if ((_stricmp(inputToCheck[0], "UPDATE") == 0)) {
                            throw new ProjectExceptionChecker("Too few arguments");
                            return 0;
                        }
                    }
        return 1;
	}


};
