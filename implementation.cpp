#include "implementation.h"
using namespace std;

ToDo::ToDo() {
    complete_file = "complete.txt";
    task_file = "task.txt";
    meta_file = "meta.txt";
}

string ToDo::cmd_ls() {
     vector<string> output = display_data(task_file);
     if (output[1] != "0") {
         return output[0];
     }
     else {
         return "There are no pending tasks!";
     }
}

// ADD NEW TASK TO THE LIST
string ToDo::cmd_add(string priority, string task) {
    try {
        // Validating the priority as non-negative number
        if (!is_number(priority) || stoi(priority) < 0) {
            throw "Error: priority " + priority + " is invalid. Nothing added.\n";
        }
        else {
            fstream file;
            string temp;
            string new_task = "";
            new_task += priority + " " + task;
            vector<string> tasks;

            // Retrieving previous tasks into vector
            file.open(task_file, ios::in);
            if (file) {
                while (!file.eof()) {
                    getline(file, temp);
                    if (temp.size() == 0) {
                        continue;
                    }
                    tasks.push_back(temp);
                }
            }
            file.close();

            // Adding new task to the vector
            tasks.push_back(new_task);

            // Sorting task according to priority
            sort(begin(tasks), end(tasks));

            // Writing updated Task List to the File
            file.open(task_file, ios::out);
            for (int i = 0; i < tasks.size() - 1; i++) {
                file << tasks[i] << endl;
            }
            file << tasks[tasks.size() - 1];
            file.close();

        }
    }
    catch (string error) {
        return error;
    }

    return "Added task: \"" + task  + "\" priority " + priority + "\n";

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

string ToDo::cmd_report() {
    vector<string> output_pending = display_data(task_file);
    vector<string> output_completed = display_data(complete_file);
    string output;
    output = "Pending : " + output_pending[1] + "\n";
    output += output_pending[0];
    output += "\nCompleted : " + output_completed[1] + "\n";
    output += output_completed[0];
    return output;
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

vector<string> display_data(string filename) {
    ifstream fin;
    string task;
    string temp_output_1;
    string temp_output_2;
    vector<string> output;
    int files_count = 0;
    fin.open(filename);
    if (fin) {
        while(!fin.eof()) {
            getline(fin, task);
            if (task.size() == 0) {
                continue;
            }
            files_count++;
            temp_output_1 += to_string(files_count) + ". " + task + "\n";
        }
    }
    fin.close();
    temp_output_2 = to_string(files_count);
    output.push_back(temp_output_1);
    output.push_back(temp_output_2);
    return output;
}

string error_msg(int i) {
    vector<string> errors_mgs = {"Error: Missing tasks string. Nothing added!", "Error: Missing NUMBER for deleting tasks."};
    return errors_mgs[i];
}