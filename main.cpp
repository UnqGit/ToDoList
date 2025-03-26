#include <iostream>
#include <string>
#include "ToDo.h"

enum options{SHOW = 1, CREATE, DELETE, COMPLETE, INCOMPLETE, PRIORITY, EDIT};

int main(){
    lists();
    int i = 0;
    while(true){
        int option = get_option();
        std::string quit;
        switch(option){
            case SHOW: show_task(); break;
            case CREATE: create_task(); break;
            case DELETE: delete_task(); break;
            case COMPLETE: mark_complete(); break;
            case INCOMPLETE: mark_incomplete(); break;
            case PRIORITY: set_priority(); break;
            case EDIT: edit_task(); break;
        }
        i++;
        save_list();
        quit = getInput("Enter /q to quit the program or hit enter to continue:\n", 1);
        if(quit == "/q") break;
        if(i % 3 == 0) save_data();
    }
    save_data();
}
