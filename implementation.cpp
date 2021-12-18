#include "implementation.h"

using namespace std;

ToDo::ToDo() {
    complete_file = "complete.tx";
    task_file = "task.txt";
}

void ToDo::cmd_ls() {
    ifstream fin;
    string task;
    int files_count = 0;
    fin.open(task_file);
    getline(fin, task);
    while(fin) {
        files_count++;
        cout << files_count << ". " << task << endl;
        getline(fin, task);
    }

    fin.close();
}

void ToDo::cmd_add(string priority, string task) {
    int index = upper_bound(priority_queue.begin(), priority_queue.end(), stoi(priority)) - priority_queue.begin();
    string before, after;
    string new_line = task + " [" + priority + "]" + "\n";
    string line;
    priority_queue.insert(index + priority_queue.begin(), stoi(priority));
    ifstream fin;
    fin.open(task_file);
    while (fin) {
        getline(fin, line);
        if (index--) {
            before += line + "\n";
        }
        else{
            after += line + "\n";
        }
    }
    fin.close();
    ofstream  fout;
    fout.open(task_file);
    fout << before << new_line << after;
    fout.close();
}

void ToDo::cmd_delete(string task_no) {
}   

void ToDo::cmd_complete(string task_no) {
}

void ToDo::cmd_report() {
    ifstream fin;
    string task;
    int files_count = 0;
    fin.open(task_file);
    cout << "Pending : " << endl;
    getline(fin, task);
    while(fin) {
        files_count++;
        cout << files_count << ". " << task << endl;
        getline(fin, task);

    }
    fin.close();
    cout << "Completed : " << endl;
    fin.open(complete_file);
    getline(fin, task);
    while(fin) {
        files_count++;
        cout << files_count << ". " << task << endl;
        getline(fin, task);
    }

    fin.close();
}

void ToDo::cmd_done(string priority) {

}

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