//WELCOME
#include <iostream>
#include <string>
#include "ToDo.h"
enum options{SHOW = 1, CREATE, DELETE, COMPLETE, INCOMPLETE, PRIORITY, EDIT};
int main(){
    lists();
    int i = 0;
    bool show = false;
    while(true){
        int option = get_option();
        if(!show) std::cout << "\033[H\033[J";
        std::string quit;
        switch(option){
            case SHOW: show_task(); show = true; break;
            case CREATE: create_task(); show = false; break;
            case DELETE: delete_task(); show = false; break;
            case COMPLETE: mark_complete(); show = false; break;
            case INCOMPLETE: mark_incomplete(); show = false; break;
            case PRIORITY: set_priority(); show = false; break;
            case EDIT: edit_task(); show = false; break;
        }
        i++;
        save_list(); //saves lists every iterations
        quit = getInput("\nEnter /q to quit the program or hit enter to continue:\n", 1);
        if(quit == "/q") break;
        if(i % 4 == 0) save_data(); //auto save(not saving every iterations as might be a bit heavy for just a to-do list)
    }
    save_data(); //save and exit
}
//BYE..?
