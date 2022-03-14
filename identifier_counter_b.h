/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Header file for identifier_counter_b.cpp.
*/

#pragma once

#include "identifier.h"
#include "bst_node.h"
#include <string>
#include <vector>

int get_var_count(bst_node *root);

int get_fun_count(bst_node *root);

int get_if_count(std::vector<std::vector<std::string>> &tokens);

int get_for_count(std::vector<std::vector<std::string>> &tokens);

int get_while_count(std::vector<std::vector<std::string>> &tokens);