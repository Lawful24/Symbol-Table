/*
* Author: László Tárkányi
* 
* Last modified: 23/4/2021
* 
* Header file for identifier_finder.cpp.
*/

#pragma once

#include "identifier.h"
#include <vector>
#include <string>

void set_identifier_values(identifier &id, std::string name, int line, int id_structure, std::string type);

void populate_ids_vector(std::vector<std::vector<std::string>> &tokens, std::vector<identifier> &ids);