#pragma once

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <vector>

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
