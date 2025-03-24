#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <limits>
#include <vector>

struct DATA{
    std::string description = "";
    bool completed = 0;
};

std::map<std::string, DATA> list;
std::vector<std::string> priority_list;

int get_option(){
    int option;
    std::cout << "What do you want to do:";
    std::cout << "\n1. Show tasks.\n2. Create task.\n3. Delete task.\n4. Mark task complete.\n5. Mark task incomplete.\n6. Set priority.\n7. Edit a task.\n";
    std::cout << "Enter your choice:\n";
    while(!(std::cin >> option) || option < 1 || option > 7){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Incorrect choice option.\nEnter choice again:\n";
    }
    return option;
}

void lists(){
    std::ifstream in("tasks.txt");
    if(!in){
        std::cout << "Couldn't open the file.\n";
        return;
    }
    else if(in.peek() == std::ifstream::traits_type::eof()) return;
    std::stringstream buffer;
    std::vector<std::pair<std::string, int>> temp;
    buffer << in.rdbuf();
    std::string tasks = buffer.str();
    std::string title, description, status, priority;
    std::stringstream ss(tasks);
    while(std::getline(ss, title, '\0') && std::getline(ss, description, '\0') && std::getline(ss, status, '\0') && std::getline(ss, priority, '\n')){
        DATA data = {description, status == "1"};
        list[title] = data;
        int prior = (priority.empty() ? -1 : stoi(priority));
        temp.emplace_back(title, prior);
    }
    std::sort(temp.begin(), temp.end(), [](auto& a, auto& b){
        if (a.second == -1) return false;
        if (b.second == -1) return true;
        return a.second < b.second;
    });
    for (auto& [task, _] : temp) {
        if(list[task].completed) continue;
        priority_list.push_back(task);
    }
}

void show_task(){
    if(list.size==0){
        std::cout << "No tasks yet.\n";
        return;
    }
    
}

void create_task(){
    
}

void delete_task(){
    
}

void mark_complete(){
    
}

void mark_incomplete(){
    
}

void set_priority(){
    
}

void save_list(){
    
}
