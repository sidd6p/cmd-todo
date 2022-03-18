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
            vector<Task> tasks = get_tasks(task_file);
            Task obj(task , stoi(priority));
            tasks.push_back(obj);

            sort(tasks.begin(), tasks.end(), sort_task);
            
            ofstream fout;
            fout.open(task_file);

            for (auto task : tasks) {
                fout.write((char*)&task, sizeof(task));
            }

            fout.close();

            return "Added task: \"" + obj.task  + "\" priority " + to_string(obj.priority) + "\n";
        }
    }
    catch (string error) {
        return error;
    }
}

string ToDo::cmd_delete(string task_index) {
    Task del_task;
    try {
        // validating the task_no as positive number
        if (!is_number(task_index) || stoi(task_index) <= 0) {
            throw "Error: Index " + task_index + " is invalid. Nothing deleted.\n";
        }
        else {
            vector<Task> tasks = get_tasks(task_file);

            if (tasks.size() < stoi(task_index)) {
                throw "Error: Index " + task_index + " does not exists. Nothing deleted.\n";
            }
            else {
                del_task = tasks[stoi(task_index) - 1];
                tasks.erase(tasks.begin() + stoi(task_index) - 1);

                ofstream fout;
                fout.open(task_file);

                for (auto task : tasks) {
                    fout.write((char*)&task, sizeof(task));
                }

                fout.close();
            }
        }
    }
    catch (string error) {
        return error;
    }
    return "Deleted task (task's priority): " + del_task.task + " #" + to_string(del_task.priority) + "\n";    
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
    int index = 1;
    for (auto task : tasks) {
        cout << index++ << ": " << task.task << " (Priority #" << task.priority << ")" << endl; 
    }
    cout << endl << endl;

    return ;
}