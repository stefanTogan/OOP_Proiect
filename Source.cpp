#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "CommandParser.h"
#include "Tables.h"
using namespace std;


int main()
{
    try {
        CommandParser parse1("SELECT ALL FROM a WHERE a = d");
        parse1.startParse();
        //parse1.getInfo();
    }
    catch (ProjectExceptionParser* err) {
        cout << err->getError();
        delete err;
    }
}