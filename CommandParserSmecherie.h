#pragma once
#include "CreateTable.h"
#include "CreateIndex.h"
#include "DropTable.h"
#include "DropIndex.h"
#include "DisplayTable.h"
#include "InsertInto.h"
#include "DeleteFrom.h"
#include "Update.h"
#include "Select.h"
#include "InputMaker.h"
#include "Checker.h"
#include <string>
using namespace std;

class ProjectExceptionParser : exception
{
    string error = "Invalid input";
public:
    ProjectExceptionParser() {

    }
    ProjectExceptionParser(string err) {
        this->error = err;
    }

    string getError() {
        return error;
    }
};

//vector<string> commands = { "Create Table" };


class CommandParser
{
    string reader= "";  //Receives input from console
    char** input=nullptr; //Matrix with all words in the input
    int nrWords = 0;  //Number of words in the input, matrix
    //CreateTable tables[100];

    const static int INPUT_LENGHT_MAX = 200;
public:
    //constructor, gets command from console

    CommandParser(string word)
    {
        if (word.length() > 0 && word.length() < INPUT_LENGHT_MAX) 
        {  
            InputMaker inputMaker(word, CommandParser::INPUT_LENGHT_MAX);
            this->reader += word;
            this->nrWords = inputMaker.determineNrWords();
            char** cuv = inputMaker.transform();

            this->input = inputMaker.adjust(cuv, this->nrWords);
        }
        else
        {
            throw new ProjectExceptionParser();
        }
    }

    //copy constructor
    CommandParser(const CommandParser& cp) {
        
        this->reader = cp.reader;
        this->nrWords = cp.nrWords;
        if (this->input != nullptr) {
            for (int i = 0; i < this->nrWords; i++)
                delete[] this->input[i];
            delete[] this->input;
        }

        InputMaker inputMaker(cp.reader, CommandParser::INPUT_LENGHT_MAX);
        this->input = inputMaker.adjust(cp.input, cp.nrWords);
    }
    
    //the destroyer
    ~CommandParser() {
        if (this->input != nullptr) {
            for (int i = 0; i < this->nrWords; i++)
                delete[] this->input[i];
            delete[] this->input;
        }
    }

    int getNrWord()
    {
        return this->nrWords;
    }

    string getReader()
    {
        return this->reader;
    }

    //starts to parse input
    void startParse() {
        try
        {
            Checker cheker;
            bool adev = cheker.checkLenght(this->input, this->nrWords);
        }
        catch (ProjectExceptionChecker* err)
        {
            cout << err->getError();
            delete err;
        }
        int ok = 0;
        if ((_stricmp(this->input[0], "CREATE") == 0) && (_stricmp(this->input[1], "TABLE") == 0)) {
            CreateTable create(this->input + 2, this->nrWords);
            ok = 1;
            try {
                create.startCreate();
            }
            catch (ProjectExceptionCreateTable* err) {
                cout <<endl<<"Invalid CREATE TABLE command format";
                delete err;
            }
        }
        if ((_stricmp(this->input[0], "CREATE") == 0) && (_stricmp(this->input[1], "INDEX") == 0) && (_stricmp(this->input[3], "ON") == 0)) {
            CreateIndex create(this->input + 2, this->nrWords);
            ok = 1;
            try {
                create.startIndex();
            }
            catch (ProjectExceptionCreateIndex* err) {
                cout << endl << "Invalid CREATE INDEX command format";
                delete err;
            }
        }
        if ((_stricmp(this->input[0], "DROP") == 0) && (_stricmp(this->input[1], "TABLE") == 0)) {
            DropTable drop(input[2]);
            ok = 1;
            try {
                drop.startDropTable(this->nrWords);
            }
            catch (ProjectExceptionDropTable* err) {
                cout << endl << "Invalid DROP TABLE command";
                delete err;
            }
        }
        if ((_stricmp(this->input[0], "DROP") == 0) && (_stricmp(this->input[1], "INDEX") == 0)) {
            DropIndex drop(input[2]);
            ok = 1;
            try {
                drop.startDropIndex(this->nrWords);
            }
            catch (ProjectExceptionDropIndex* err) {
                cout << endl << "Invalid DROP INDEX command";
                delete err;
            }
        }
        if ((_stricmp(this->input[0], "DISPLAY") == 0) && (_stricmp(this->input[1], "TABLE") == 0)) {
            DisplayTable table(this->input[2]);
            ok = 1;
            try {
                table.startDisplayTable(this->nrWords);
            }
            catch (ProjectExceptionDisplayTable* err) {
                cout << endl << "Invalid DISPLAY TABLE command";
                delete err;
            }
        }
        if ((_stricmp(this->input[0], "INSERT") == 0) && (_stricmp(this->input[1], "INTO") == 0) && (_stricmp(this->input[3], "VALUES") == 0)) {
            InsertInto insert(this->input + 2, this->nrWords);
            ok = 1;
            try {
               insert.startInsert();
            }
            catch (ProjectExceptionInsertInto* err) {
                cout << endl << "Invalid INSERT INTO command format";
                delete err;
            }
        }
        if ((_stricmp(this->input[0], "DELETE") == 0) && (_stricmp(this->input[1], "FROM") == 0) && (_stricmp(this->input[3], "WHERE") == 0)) {
            DeleteFrom del(this->input + 2, this->nrWords);
            ok = 1;
            try {
                del.startDelete();
            }
            catch (ProjectExceptionDeleteFrom* err) {
                cout << endl << "Invalid DELETE FROM command format";
                delete err;
            } 
        }
        if ((_stricmp(this->input[0], "UPDATE") == 0) && (_stricmp(this->input[2], "SET") == 0)) {
            Update update(this->input + 1, this->nrWords);
            ok = 1;
            try {
                update.startUpdate();
            }
            catch (ProjectExceptionUpdate* err) {
                cout<< endl << "Invalid UPDATE command format";
                delete err;
            }
        }
        if (_stricmp(this->input[0], "SELECT") == 0) {

            Select select;
            try {
                select.checkFormat(this->input + 1, this->nrWords - 1);
                select.addInformation(this->input + 1, this->nrWords-1);
                select.startSelect();
            }
            catch (ProjectExceptionSelect* err) {
                cout << endl << "Invalid SELECT command format";
                delete err;
            }
            
            ok = 1;
        }
        if (ok == 0) {
            cout << endl << "Invalid input";
        }
    }


    void getInfo()
    {
        cout <<this->reader<<endl;
        for (int i = 0; i < this->nrWords; i++) {
            cout << this->input[i]<< endl;
        }
        cout << this->nrWords;
    }

    //operators
    CommandParser operator=(const CommandParser& cp) {
        if (this != &cp) {
            this->reader = cp.reader;
            this->nrWords = cp.nrWords;
            if (this->input != nullptr) {
                for (int i = 0; i < this->nrWords; i++)
                    delete[] this->input[i];
                delete[] this->input;
            }

            InputMaker inputMaker(cp.reader, CommandParser::INPUT_LENGHT_MAX);
            this->input = inputMaker.adjust(cp.input, cp.nrWords);
        }
        return *this;
    }

    bool operator==(const CommandParser& cp)
    {
        if (this->nrWords != cp.nrWords)
            return 0;
        else
        {
            if (this->reader.compare(cp.reader.c_str()) != 0)
                return 0;
        }
        return 1;
    }

    char* operator[](int i)
    {
        if (i < nrWords)
            return this->input[i];
        else
            throw ProjectExceptionParser();
    }

    CommandParser operator+(const char* newCommand)
    {
        CommandParser newParser(newCommand);
        return newParser;
    }

    CommandParser operator!()
    {
        CommandParser result = *this;
        string command = string(result.input[0]);
        if (command == "CREATE" || command == "DROP")
        {
            if (command == "CREATE")
                strcpy(result.input[0], "DROP");
            else
                strcpy(result.input[0], "CREATE");
        }
        return result;
    }

    operator string() const
    {
        return this->reader;
    }

    friend istream& operator>>(istream& stream, CommandParser& cp);
  
};

void operator<<(ostream& stream, CommandParser& cp)
{
    cp.getInfo();
}

istream& operator>>(istream& stream, CommandParser& cp)
{
    string inputFromConsole;
    cout << "Introduce command:";
    getline(stream, inputFromConsole);
    InputMaker inputMaker(inputFromConsole, CommandParser::INPUT_LENGHT_MAX);
    if (cp.input != nullptr)
    {
        for (int i = 0; i < cp.getNrWord(); i++)
            delete[] cp.input[i];
        delete[] cp.input;
    }
    cp.nrWords = inputMaker.determineNrWords();
    cp.reader = inputFromConsole;
    char** cuv = inputMaker.transform();

    cp.input = inputMaker.adjust(cuv,cp.nrWords);
    
    return stream;
}

bool operator>(CommandParser& left, CommandParser& right)
{
    bool sameNumber = (left.getNrWord() > right.getNrWord());
    return sameNumber;
}