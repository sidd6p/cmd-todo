#include "implementation.h"
#include "support.h"

using namespace std;

ToDo::ToDo() {
    complete_file = "complete.tx";
    task_file = "task.txt";
    meta_file = "meta.txt";
}

string ToDo::cmd_ls() {
    return display_data(task_file);
}

string ToDo::cmd_add(string priority, string task) {
    //validating the priority as non-negative number
    if (!is_number(priority) || stoi(priority) < 0) {
        return "Error: priority " + priority + " is invalid. Nothing added.\n";
    }
    // initalise
    string queue = "", lines = "", temp="";
    string new_line = task + " [" + priority + "]";
    fstream file;
    vector<string> output;
    vector<int> priority_queue;

    // getting priority data from meta_file andupdating meta_file with new task priority 
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

    // getting the right index to insert new task in task_file
    sort(priority_queue.begin(), priority_queue.end());
    vector<int>::iterator index_itr = upper_bound(priority_queue.begin(), priority_queue.end(), stoi(priority));
    int index = index_itr - priority_queue.begin() - 1;

    //updating new task into output vector
    file.open(task_file, ios::in);
    if(file) {
        while(!file.eof()) {
            getline(file, lines);
            output.push_back(lines);
        }
    }
    output.insert(output.begin() + index, new_line);
    file.close();
    
    // inserting output vector into task_file
    file.open(task_file, ios::out);
    for (auto i=0; i<output.size()-1; i++) {
        file << output[i] << endl;
    }
    file << output[output.size()-1];
    file.close();

    //updating meta_file
    file.open(meta_file, ios::out);
    for (auto i=0; i<priority_queue.size(); i++) {
        file << priority_queue[i] << " ";
    }
    file.close();

    return "Added task: \"" + task  + "\" priority" + priority + "\n";

}

string ToDo::cmd_delete(string task_no) {
    //validating the task_no as positive number
    if (!is_number(task_no) || stoi(task_no) <= 0) {
        return "Error: item with index " + task_no + " does not exist. Nothing deleted.\n";
    }

    //initalise
    string queue = "", lines = "", temp="";
    fstream file;
    int index = 1;
    vector<string> output;

    //populate output vector with task_file
    file.open(task_file, ios::in);
    if(file) {
        while(!file.eof()) {
            getline(file, lines);
            output.push_back(lines);
        }
    }
    file.close();

    //valading task_no as a proper index
    if (stoi(task_no) > output.size()) {
        return "Error: item with index " + task_no + " does not exist. Nothing deleted.\n";
    }

    //updating task_file 
    output.erase(output.begin() + stoi(task_no) - 1);
    file.open(task_file, ios::out);
    for (auto i=0; i<output.size()-1; i++) {
        file << output[i] << endl;
    }
    file << output[output.size()-1];
    file.close();
       
    //updating meta_file 
    file.open(meta_file, ios::in);
    getline(file, queue);
    file.close();
    stringstream ss(queue);
    queue = "";
    index = 1;
    file.open(meta_file, ios::out);
    while (ss >> queue) {
        if (index++ != stoi(task_no)) {
            file << queue << " ";
        }
    }
    file.close();

    return "Deleted item with index " + task_no + "\n";    
}   

string ToDo::cmd_report() {
    string output;
    output = "Pending :\n";
    output += display_data(task_file);
    output += "Completed :\n";
    output += display_data(complete_file);
    return output;
}

string ToDo::cmd_done(string priority) {
    return "done\n";
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