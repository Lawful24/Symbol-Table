/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Header file for io_file_handler.cpp.
*/

#pragma once

#include "identifier.h"
#include "bst_node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> get_text_from_file(std::string file_name);

std::vector<std::vector<std::string>> get_tokens_from_data(std::vector<std::string> &data);

void write_output_file(bst_node *root, std::ofstream &file_pointer);