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
        if (word.length() > 0 && word.length() < INPUT_LENGHT_MAX)  //checks lenght of input from conole
        {
            char input[INPUT_LENGHT_MAX];
            this->reader += word;
            strcpy(input, this->reader.c_str()); 
            char cuv[20][INPUT_LENGHT_MAX];       //makes matrix of words
            char* p;
            p = strtok(input, " (),=");
            while (p != NULL)
            {
                strcpy(cuv[this->nrWords], p);
                this->nrWords++;
                p = strtok(NULL, " (),=");
            }
            
            this->input = new char* [this->nrWords];  //copies matrix of words into class atribute input
            for (int i = 0; i < this->nrWords; i++) {
                this->input[i] = new char[strlen(cuv[i]) + 1];
            }
            for (int i = 0; i < this->nrWords; i++) {
                strcpy(this->input[i], cuv[i]);
            }
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
        this->input = new char* [this->nrWords];
        for (int i = 0; i < this->nrWords; i++) {
            this->input[i] = new char[strlen(cp.input[i]) + 1];
        }
        for (int i = 0; i < this->nrWords; i++) {
            strcpy(this->input[i], cp.input[i]);
        }
    }
    
    //the destroyer
    ~CommandParser() {
        if (this->input != nullptr) {
            for (int i = 0; i < this->nrWords; i++)
                delete[] this->input[i];
            delete[] this->input;
        }
    }

    //starts to parse input
    void startParse() {
        int ok = 0;
        this->checkLenght();
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


    //check lengs of input so we dont compare in matrix on positions that dont exist
    bool checkLenght() {
        if (this->nrWords == 0) {
            throw new ProjectExceptionParser("Empty command received");
            return 0;
        }
        else
            if (this->nrWords <= 2) {
                throw new ProjectExceptionParser("Too few arguments");
                return 0;
            }
            else
                if (this->nrWords < 4) {
                    if ((_stricmp(this->input[0], "CREATE") == 0) && (_stricmp(this->input[1], "INDEX") == 0)) {
                        throw new ProjectExceptionParser("Too few arguments");
                        return 0;
                    }
                    if ((_stricmp(this->input[0], "INSERT") == 0) && (_stricmp(this->input[1], "INTO") == 0)) {
                        throw new ProjectExceptionParser("Too few arguments");
                        return 0;
                    }
                    if ((_stricmp(this->input[0], "DELETE") == 0) && (_stricmp(this->input[1], "FROM") == 0)) {
                        throw new ProjectExceptionParser("Too few arguments");
                        return 0;
                    }
                    if ((_stricmp(this->input[0], "UPDATE") == 0)) {
                        throw new ProjectExceptionParser("Too few arguments");
                        return 0;
                    }
                }
                else
                    if (this->nrWords < 5) {
                        if ((_stricmp(this->input[0], "UPDATE") == 0)) {
                            throw new ProjectExceptionParser("Too few arguments");
                            return 0;
                        }
                    }
        return 1;
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
            this->input = new char* [this->nrWords];
            for (int i = 0; i < this->nrWords; i++) {
                this->input[i] = new char[strlen(cp.input[i]) + 1];
            }
            for (int i = 0; i < this->nrWords; i++) {
                strcpy(this->input[i], cp.input[i]);
            }
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
};
