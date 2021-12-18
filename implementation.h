#pragma once 
#include <iostream>

using std::string;

class ToDo {
    private:
        string complete;
        string task;
    public:
        ToDo();
        string cmd_ls();
        bool cmd_add(string , string);
        bool cmd_delete(string );
        bool cmd_complete(string );
        string cmd_report();
        string cmd_help();
};