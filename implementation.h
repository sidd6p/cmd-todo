#pragma once 
#include <bits/stdc++.h>

using namespace std;


class Task {
    public:
        string task;
        int priority;
    public:
        Task () {

        }
        Task(string task, int priority) {
            this->task = task;
            this->priority = priority;
        }
};


class ToDo {
    private:
        string complete_file;
        string task_file;
        string meta_file;
        string my_buff;
    public:
        ToDo();
        vector<Task> cmd_ls();
        string cmd_add(string , string);
        string cmd_delete(string);
        vector<vector<Task>> cmd_report();
        string cmd_done(string);
        string cmd_help();
        vector<Task> get_tasks(string);
};


bool is_number(string);
vector<string> display_data(string);
string error_msg(int); 
void display(vector<Task> &);
bool sort_task(Task&, Task&);