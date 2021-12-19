#include "implementation.h"

using namespace std;

ToDo::ToDo() {
    complete_file = "complete.tx";
    task_file = "task.txt";
    meta_file = "meta.txt";
}

void ToDo::cmd_ls() {
    ifstream fin;
    string task;
    int files_count = 0;
    fin.open(task_file);
    if (fin) {
        while(!fin.eof()) {
            getline(fin, task);
            files_count++;
            cout << files_count << ". " << task << endl;
        }
    }

    fin.close();
}

void ToDo::cmd_add(string priority, string task) {
    string before = "", after = "", queue = "", lines = "", temp="";
    string new_line = task + " [" + priority + "]";
    fstream file;
    vector<string> output;

    file.open(meta_file, ios::in);
    getline(file, queue);
    queue += priority + " ";
    stringstream ss(queue);
    file.close();
    file.open(meta_file, ios::out);
    file << queue << endl;
    file.close();

    while (ss >> temp) {
        priority_queue.push_back(stoi(temp));
    }

    sort(priority_queue.begin(), priority_queue.end());
    vector<int>::iterator index_itr = upper_bound(priority_queue.begin(), priority_queue.end(), stoi(priority));
    int index = index_itr - priority_queue.begin() - 1;

    file.open(task_file, ios::in);
    if(file) {
        while(!file.eof()) {
            getline(file, lines);
            output.push_back(lines);
        }
    }
    output.insert(output.begin() + index, new_line);
    file.close();
    
    file.open(task_file, ios::out);
    for (auto i=0; i<output.size()-1; i++) {
        file << output[i] << endl;
    }
    file << output[output.size()-1];
    file.close();
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
    if (fin) {
        while(!fin.eof()) {
            files_count++;
            cout << files_count << ". " << task << endl;
            getline(fin, task);

        }
    }
    fin.close();
    cout << "Completed : " << endl;
    fin.open(complete_file);
    getline(fin, task);
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
            "$ ./task report               # Statistics";
    return help_msg;
}