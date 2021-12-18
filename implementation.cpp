#include "implementation.h"

ToDo::ToDo() {
    
}

string ToDo::cmd_ls() {
    return "cmd_ls";
}

bool ToDo::cmd_add(string priority, string task) {
    return true;
}

bool ToDo::cmd_delete(string task_no) {
    return true;
}   

bool ToDo::cmd_complete(string task_no) {
    return true;
}

string ToDo::cmd_report() {
    return "cmd_report";
}

string ToDo::cmd_help() {
    return "cmd_help";
}