#include <fstream>
#include "implementation.h"

using namespace std;

ToDo::ToDo() {
    complete_file = "complete.txt";
    task_file = "task.txt";
}

vector<Task> ToDo::cmd_ls() {
     return get_tasks(task_file);
}

// ADD NEW TASK TO THE LIST
string ToDo::cmd_add(string priority, string task) {
    try {
        // Validating the priority as non-negative number
        if (!is_number(priority) || stoi(priority) < 0) {
            throw "Error: priority " + priority + " is invalid. Nothing added.\n";
        }
        else {
            Task obj(task , stoi(priority));
            
            ofstream fout;
            fout.open(task_file, ios::app);

            fout.write((char*)&obj, sizeof(obj));

            fout.close();

            return "Added task: \"" + obj.task  + "\" priority " + to_string(obj.priority) + "\n";
        }
    }
    catch (string error) {
        return error;
    }
}

string ToDo::cmd_delete(string task_index) {
    string del_task = "";
    try {
        // validating the task_no as positive number
        if (!is_number(task_index) || stoi(task_index) <= 0) {
            throw "Error: Index " + task_index + " is invalid. Nothing deleted.\n";
        }
        else {
            fstream file;
            vector<string> tasks;
            string task;
            bool has_task = false;
            int cur_index = 1;

            // Getting task with given index
            file.open(task_file, ios::in);
            if (file) {
                while (!file.eof()) {
                    getline(file, task);
                    if (cur_index == stoi(task_index)) {
                        has_task = true;
                        del_task += task;
                    }
                    else {
                        tasks.push_back(task);
                    }
                    cur_index++;
                } 
            }
            file.close();

            // No task exists with given index
            if (has_task == false) {
                throw "Error: item with index " + task_index + " does not exist. Nothing deleted.\n";
            } 
            else {
                // Updating task file
                file.open(task_file, ios::out);
                for (int i = 0; i < tasks.size() - 1; i++) {
                    file << tasks[i] << endl;
                }
                file << tasks[tasks.size() - 1];
                file.close();
            }            
        }
    }
    catch (string error) {
        return error;
    }
    return "Deleted item (priority task): " + del_task + "\n";    
}   

string ToDo::cmd_done(string index) {
    string temp = cmd_delete(index);
    string msg = "Error";
    size_t pos = temp.find(msg);
    if (pos != string::npos) {
        return "Error: no incomplete item with index " + index + " exists.\n";
    }
    my_buff = my_buff.substr(0, my_buff.size()-3);
    ifstream file_temp;
    file_temp.open(complete_file);
    char c = file_temp.peek();
    file_temp.close();
    ofstream file;
    file.open(complete_file, ios::app);
    if (c == EOF) {
        file << my_buff;
    }
    else {
        file << endl << my_buff;
    }
    file.close();
    return "Marked item as done.\n";
}

vector<vector<Task>> ToDo::cmd_report() {
    vector<vector<Task>> report;
    report.push_back(get_tasks(task_file));
    report.push_back(get_tasks(complete_file));
    return report;
}



// RETURN COMMAND DETAILS
string ToDo::cmd_help() {
    string help_msg =  "Usage :-\n"
            "$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n"
            "$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order\n" 
            "$ ./task del INDEX            # Delete the incomplete item with the given index\n" 
            "$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n" 
            "$ ./task help                 # Show usage\n"
            "$ ./task report               # Statistics\n";
    return help_msg;
}



bool is_number(string nums) {
    for (char const num : nums) {
        if (std::isdigit(num) == 0) {
            return false;
        }
    }
    return true;
}

vector<Task> ToDo::get_tasks(string filename) {
    ifstream fin;
    Task obj;
    vector<Task> tasks;

    fin.open(filename, ios::in);

    if(!fin) {
        return tasks;
    }

    fin.read((char*)&obj, sizeof(obj));

    while (!fin.eof()) {
        tasks.push_back(obj);
        fin.read((char*)&obj, sizeof(obj));
    }

    sort(tasks.begin(), tasks.end(), sort_task);

    return tasks;
}

string error_msg(int i) {
    vector<string> errors_mgs = {"Error: Missing tasks string. Nothing added!", "Error: Missing NUMBER for deleting tasks."};
    return errors_mgs[i];
}

bool sort_task(Task &a, Task &b) {
    if (a.priority < b.priority) {
        return true;
    }
    else {
        return false;
    }
}

void display(vector<Task> &tasks) {
    cout << "Total: " << tasks.size() << endl;
    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ": " << tasks[i].task << " (Priority #" << tasks[i].priority << ")" << endl; 
    }
    cout << endl << endl;

    return ;
}