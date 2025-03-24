#include <iostream>
#include <string>
#include "ToDo.h"

enum options{ SHOW = 1, CREATE, DELETE, COMPLETE, INCOMPLETE, PRIORITY};

int main(){
    lists();
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
        }
        save_list();
        std::cout << "\nQuit?(y/n)\n";
        std::getline(std::cin, quit);
        for(char& c : quit) c = std::tolower(c);
        if(quit.find('y') != std::string::npos || quit.find('1') != std::string::npos) break;
    }
}
