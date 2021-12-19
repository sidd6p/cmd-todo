#pragma once 
#include <bits/stdc++.h>

using namespace std;

class ToDo {
    private:
        string complete_file;
        string task_file;
        string meta_file;
        vector<int> priority_queue;
    public:
        ToDo();
        void cmd_ls();
        void cmd_add(string , string);
        void cmd_delete(string);
        void cmd_complete(string);
        void cmd_report();
        void cmd_done(string);
        string cmd_help();
};