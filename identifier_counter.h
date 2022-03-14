/*
* Author: László Tárkányi
* 
* Last modified: 23/4/2021
* 
* Header file for identifier_counter.cpp.
*/

#pragma once

#include "identifier.h"
#include <string>
#include <vector>

int get_var_count(std::vector<identifier> &ids);

int get_fun_count(std::vector<identifier> &ids);

int get_if_count(std::vector<std::vector<std::string>> &tokens);

int get_for_count(std::vector<std::vector<std::string>> &tokens);

int get_while_count(std::vector<std::vector<std::string>> &tokens);