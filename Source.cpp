#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "CommandParser.h"
#include "Tables.h"
#include "InputMaker.h"
#include "CommandExtractor.h"
#include "TextFileOperator.h"
#include "CommandHandler.h"
using namespace std;





int main(int argc, char* argv[]) {

	cout << endl << "The app is " << argv[0];

	CommandHandler ch(argc);
	ch.startHandle(argv);
	

}

