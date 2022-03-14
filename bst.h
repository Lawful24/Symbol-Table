/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Header file for bst.cpp.
*/

#pragma once

#include "bst_node.h"
#include "identifier.h"
#include <string>

class bst
{
private:
	bst_node* root;

public:
	bst();
	
	~bst();
	
	bst_node* get_root();
	
	void update(identifier new_id);
	
	bool bst::contains(bst_node* node, std::string key);
	
	void print_table(bst_node *node);
};