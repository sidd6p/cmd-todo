#include <iostream>
#include "implementation.h"

using namespace std;

int main(int argc, char *argv[]) {
    ToDo session;
    switch (argc) {
        case 2:
            if (argv[1] == "help") {
                cout << session.cmd_help() << endl;
            }
            else if (argv[1] == "ls") {
                cout << session.cmd_ls() << endl;
            }
            else if (argv[1] == "report") {
                cout << session.cmd_report() <<endl;
            }
            break;
        case 3:
            if (argv[1] == "del") {
                session.cmd_delete(argv[2]); 
            }
            else if (argv[1] == "done") {
                session.cmd_complete(argv[2]);
            }
            break;
        case 4:
            if (argv[1] == "add") {
                session.cmd_add(argv[2], argv[3]);
            }
            break;
        default:
            break;
    }
    
    return 0;
}