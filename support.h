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