/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Header file for bst_node.cpp.
*/

#pragma once

#include "identifier.h"

class bst_node
{
private:
	identifier id;
	bst_node *left;
	bst_node *right;

public:
	bst_node(identifier value);
	
	bst_node();
	
	~bst_node();
	
	identifier get_id();
	
	bst_node* get_left();
	
	bst_node* get_right();
	
	void set_id(identifier new_id);
	
	void set_left(bst_node* new_node);
	
	void set_right(bst_node* new_node);
	
	void insert(bst_node **tree, identifier new_id);
};