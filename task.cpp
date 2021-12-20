#include "implementation.h"
using namespace std;

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    ToDo session;
    if (argc == 1 || args[1] == "help") {
        cout << session.cmd_help();
        return 0;
    }
    else if (args[1] == "ls") {
        cout << session.cmd_ls();
    }
    else if (args[1] == "report") {
        cout << session.cmd_report();
    }
    else if (args[1] == "done") {
        cout << session.cmd_delete(args[2]);
    }
    else if (args[1] == "del") {
        if (argc == 2) {
            cout << error_msg(1);
        }
        else {
            cout << session.cmd_delete(args[2]);
        }
    }
    else if (args[1] == "add") {
        if (argc == 2) {
            cout << error_msg(0);
        }
        else {
            cout << session.cmd_add(args[2], args[3]);
        }
    }
    
    return 0;
}