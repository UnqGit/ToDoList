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
        std::cout << "Quit?(y/n)\n";
        std::getline(std::cin, quit);
        for(char& c : quit) c = std::tolower(c);
        if(quit.find('y') != std::string::npos || quit.find('1') != std::string::npos) break;
        if(i % 3 == 0) save_data();
    }
    save_data();
}
