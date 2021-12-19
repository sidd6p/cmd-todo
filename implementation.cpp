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
    getline(fin, task);
    while(fin) {
        files_count++;
        cout << files_count << ". " << task << endl;
        getline(fin, task);
    }

    fin.close();
}

void ToDo::cmd_add(string priority, string task) {
    string before = "", after="";
    string new_line = task + " [" + priority + "]";
    string line;
    string lines;
    ifstream fin;
    string queue = "";

    fin.open(task_file);
    getline(fin, queue);
    queue += priority + " ";

    for(auto i = 0; i != queue.size() && queue[i] != '\n'; i++) {
        if (queue[i] != ' ') {
            priority_queue.push_back(queue[i]-'0');
        }
    }

    sort(priority_queue.begin(), priority_queue.end());
    vector<int>::iterator index_itr = upper_bound(priority_queue.begin(), priority_queue.end(), stoi(priority));
    int index = index_itr - priority_queue.begin();

    getline(fin, lines);
    int i = 0;
    cout << lines << endl;
    while (i < lines.size()+1) {
        before += lines[i++];
        if (i == index) {
            before += new_line;
        }
    }

    fin.close();

    ofstream fout;
    fout.open(task_file);
    fout << before;
    // fout << queue << "\n" << before << new_line << after;
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