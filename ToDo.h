#pragma once
#include <string>
int get_option();
void lists();
std::string getInput(const std::string& prompt, int type);
void show_task();
void create_task();
void delete_task();
void mark_complete();
void mark_incomplete();
void set_priority();
void edit_task();
void save_list();
void save_data();
