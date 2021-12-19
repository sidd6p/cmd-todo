#include "implementation.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    ToDo session;
    switch (argc) {
        case 1:
            cout << session.cmd_help();
            break;
        case 2:
            if (args[1] == "help") {
                cout << session.cmd_help();
            }
            else if (args[1] == "ls") {
                cout << session.cmd_ls();
            }
            else if (args[1] == "report") {
                cout << session.cmd_report();
            }
            break;
        case 3:
            if (args[1] == "del") {
                cout << session.cmd_delete(args[2]); 
            }
            else if (args[1] == "done") {
                cout << session.cmd_done(args[2]);
            }
            break;
        default:
            if (args[1] == "add") {
                string task;
                for (auto i = 3; i < argc; i++) {
                    if (i == argc - 1){
                        task += args[i];
                    }
                    else {
                        task += args[i] + " ";
                    }
                }
                cout << session.cmd_add(args[2], task);
            }
            break;
    }
    
    return 0;
}