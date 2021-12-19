#pragma once 
#include <bits/stdc++.h>

using namespace std;

class ToDo {
    private:
        string complete_file;
        string task_file;
        string meta_file;
        string my_buff;
    public:
        ToDo();
        string cmd_ls();
        string cmd_add(string , string);
        string cmd_delete(string);
        string cmd_report();
        string cmd_done(string);
        string cmd_help();
};