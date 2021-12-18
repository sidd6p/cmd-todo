#pragma once 
#include <iostream>

using std::string;

class ToDo {
    private:
        string complete_file;
        string task_file;
    public:
        ToDo();
        void cmd_ls();
        void cmd_add(string , string);
        void cmd_delete(string );
        void cmd_complete(string );
        void cmd_report();
        string cmd_help();
};