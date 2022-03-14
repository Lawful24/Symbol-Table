/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Header file for identifier_finder_b.cpp.
*/

#pragma once

#include "identifier.h"
#include "bst.h"
#include <string>
#include <vector>

void set_identifier_values(identifier &id, std::string name, int line, int id_structure, std::string type);

void populate_identifier_tree(std::vector<std::vector<std::string>> &tokens, bst *tree);