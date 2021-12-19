#pragma once 
#include <bits/stdc++.h>

bool is_number(string nums) {
    for (char const num : nums) {
        if (std::isdigit(num) == 0) {
            return false;
        }
    }
    return true;
}

string display_data(string filename) {
    ifstream fin;
    string task;
    string output;
    int files_count = 0;
    fin.open(filename);
    if (fin) {
        while(!fin.eof()) {
            getline(fin, task);
            files_count++;
            output += to_string(files_count) + ". " + task + "\n";
        }
    }
    fin.close();
    return output;
}