#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <vector>

struct DATA{
    std::string description = "";
    bool completed = 0;
    int priority = -1;
};

std::map<std::string, DATA> list;
std::vector<std::string> priority_list;

void cin_clear(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void done(){
    std::cout << "Done.\n";
}

std::string again(bool t = 0){
    std::string ret = "Enter again";
    std::string qu = "(or \"/q\" to quit)";
    if(t) ret += qu;
    ret += ":\n";
    return ret;
}

int get_option(){
    int option;
    std::cout << "What do you want to do:";
    std::cout << "\n1. Show tasks.\n2. Create task.\n3. Delete task.\n4. Mark task complete.\n5. Mark task incomplete.\n6. Set priority.\n7. Edit a task.\n";
    std::cout << "Enter your choice:\n";
    while(!(std::cin >> option) || option < 1 || option > 7){
        cin_clear();
        std::cout << "Incorrect choice option.\n" << again();
    }
    cin_clear();
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
        int prior;
        try{
            prior = std::stoi(priority);
        }
         catch(const std::invalid_argument& e) {
            std::cerr << "Warning: Task '" << title << "' has invalid priority. Setting to default.\n";
            prior = -1;
        } 
        catch(const std::out_of_range& e) {
            std::cerr << "Warning: Task '" << title << "' has out-of-range priority. Setting to default.\n";
            prior = -1;
        }
        DATA data = {description, status == "1", prior};
        list[title] = data;
        temp.emplace_back(title, prior);
    }
    std::sort(temp.begin(), temp.end(), [](auto& a, auto& b){
        if(a.second == -1) return false;
        if(b.second == -1) return true;
        return a.second < b.second;
    });
    for (auto& [task, _] : temp) {
        if(list[task].completed) continue;
        priority_list.push_back(task);
    }
}

void printTask

void show_task(){
    if(list.empty()){
        std::cout << "No tasks yet.\n";
        return;
    }
    for(const auto& [title, data] : list){
        std::cout << "\033[93m" << title << "\033[0m" << (data.completed ? "\033[92mCOMPLETE" : "\033[91mINCOMPLETE") << "\033[0m\n";
        if(!data.description.empty()) std::cout << ": \033[97m" << data.description << "\033[0m";
        std::cout << "\n";
    }
}

void correction(std::string& input){
    input.erase(0, input.find_first_not_of(" \t\n"));
    input.erase(input.find_last_not_of(" \t\n") + 1);
}

bool numberValidation(std::string& input, int offset = 0){
    for(const char& ch : input){
        if(!std::isdigit(ch)){
            std::cout << "Err! Not a valid number.\n" << again();
            return true;
        }
    }
    int toCheck = stoi(input);
    int j = priority_list.size() + 1 - offset;
    if(toCheck == 0 || toCheck > j){
        std::cout << "Number not in bound.\n" << again() << "(valid bound = 1" << (j > 1 ? (" to " + std::to_string(j)) : "") << "):\n";
        return true;
    }
    return false;
}

std::string getInput(const std::string& prompt, int type){
    std::cout << prompt;
    auto stringValidation = [&](std::string& input){
        if(input.find('\0') != std::string::npos){
            std::cout << "Err! Invalid characters in the string.\n" << again();
            return true;
        }
        return false;
    };
    std::string input;
    bool invalid;
    do{
        std::cin.clear();
        std::getline(std::cin, input);
        correction(input);
        if(input.length() > 50 && type == 0){
            std::cout << "Title name can't be longer than 50 characters.\n" << again();
            continue;
        }
        if(input.empty() || list.find(input) != list.end()){
            if(type!=0) return (type == 2 ? "-1" : "");
            std::cout << "Err! Title can't be empty or same as one already present.\n" << again();
            continue;
        }
        invalid = (type==2 ? numberValidation(input) : stringValidation(input));
        if(!invalid) break;
    }while(true);
    std::cin.clear();
    return input;
}

void create_task(){
    std::string input = getInput("Enter the new task name(or enter \"/q\" to exit):\n", 0);
    if(input == "/q"){
        std::cin.clear();
        return;
    }
    std::string description = getInput("Enter the description(hit enter to skip):\n", 1);
    std::string priority = getInput("Set priority(hit enter to skip):\n", 2);
    int prior = stoi(priority);
    if(prior == -1 || prior == priority_list.size() + 1) priority_list.push_back(input);
    else priority_list.insert(priority_list.begin() + prior - 1, input);
    DATA data = {description, 0, prior};
    list[input] = data;
    std::cin.clear();
    done();
}

void delete_task(){
    std::string input;
    std::cout << "Enter the title of task you want to remove:\n";
    do{
        std::cin.clear();
        std::getline(std::cin, input);
        correction(input);
        if(input == "/q"){
            std::cin.clear();
            return;
        }
        if(list.find(input) != list.end()) break;
        std::cout << "Item not found.\nEnter again(or enter \"/q\" to exit):\n";
    }while(true);
    std::cin.clear();
    int prior = list.at(input).priority;
    list.erase(input);
    if(prior!=-1) priority_list.erase(priority_list.begin()+prior);
}

void congested(bool comp){
    std::string input;
    std::cout << "Enter the task name that you want to mark " << (comp?"complete":"incomplete") <<"(or \"/q\" to quit):\n";
    do{
        std::cin.clear();
        std::getline(std::cin, input);
        correction(input);
        if(input=="/q"){
            std::cin.clear();
            return;
        }
        if(list.find(input) != list.end()){
            int prior = list[input].priority;
            if(comp){ if(prior!=-1) priority_list.erase(priority_list.begin() + prior);}
            else{ if(prior==-1) priority_list.push_back(input);}
            list.at(input).completed = comp;
            done();
            std::cin.clear();
            return;
        }
        std::cout << "No such task.\n" << again(1);
    }while(true);
}

void mark_complete(){
    congested(true);
}

void mark_incomplete(){
    congested(false);
}

void prioritySet(bool edit, std::string I = ""){
    std::string input = I;
    std::string new_priority;
    bool invalid;
    int j;
    if(edit){
        std::cout << "Enter the task name(or enter \"/q\" to exit).\n";
        do{
            std::cin.clear();
            std::getline(std::cin, input);
            correction(input);
            if(input == "/q"){
                std::cin.clear();
                return;
            }
            if(list.find(input) != list.end()){
                j = list.at(input).priority;
                if(j == -1){
                    std::cout << "Can't set priority of completed tasks.\n";
                    std::cin.clear();
                    return;
                }
                std::cin.clear();
                break;
            }
            std::cout << "Task doesn't exist.\n";
        }while(true);
    }
    else j = list.at(input).priority;
    std::cin.clear();
    std::cout << "Enter the new priority(Eg: 1 has highest priority).\n";
    do{
        std::cin.clear();
        std::getline(std::cin, new_priority);
        correction(new_priority);
        if(!numberValidation(new_priority, 1)) break;
    }while(true);
    int p = stoi(new_priority);
    std::cin.clear();
    priority_list.erase(priority_list.begin() + j);
    if(p == -1 || p > priority_list.size()) priority_list.push_back(input);
    else priority_list.insert(priority_list.begin() + p - 1, input);
}

void set_priority(){
    prioritySet(true);
    std::cin.clear();
    done();
}

void edit_task(){
    std::string input, old_name, new_name;
    std::cout << "Enter the task's title you want to edit(or enter \"/q\" to exit).\n";
    do{
        std::cin.clear();
        std::getline(std::cin, input);
        correction(input);
        if(input == "/q"){
            std::cin.clear();
            return;
        }
        if(list.find(input) != list.end()){
            old_name = input;
            new_name = old_name;
            break;
        }
        std::cout << "Couldn't find the task.\n" << again();
    }while(true);
    std::cin.clear();
    auto yesno = [&](const std::string& prompt){
        std::cout << prompt;
        std::cin.clear();
        std::getline(std::cin, input);
        correction(input);
    };
    yesno("Do you want to edit the title?(y/n):\n");
    if(input == "y" || input == "Y"){
        DATA data = list.at(old_name);
        list.erase(old_name);
        new_name = getInput("Enter the new name:\n", 0);
        list[new_name] = data;
        if(data.priority != -1) priority_list[data.priority] = new_name;
    }
    yesno("Do you want to edit the description?(y/n):\n");
    if(input == "y" || input == "Y") list.at(new_name).description = getInput("Enter the new description:\n", 1);
    yesno("Do you want to edit the priority?(y/n):\n");
    if(input == "y" || input == "Y") prioritySet(false, new_name);
    std::cin.clear();
    done();
}

void save_list(){
    std::map<std::string, DATA> temp = list;
    list.clear();
    for(int i = 0; i < priority_list.size(); i++){
        std::string j = priority_list[i];
        list[j] = temp[j];
        temp.erase(j);
        list[j].priority = i;
    }
    for(const auto [title, data] : temp){
        list[title] = {data.description, 1, -1};
    }
}

void save_data(){
    std::ofstream out("tasks.txt", std::ios::trunc);
    if(!out){
        std::cout << "Error opening file.\n";
        return;
    }
    for(const auto [title, data] : list)
        out << title << '\0' << data.description << '\0' << data.completed << '\0' << data.priority << '\n';
}
