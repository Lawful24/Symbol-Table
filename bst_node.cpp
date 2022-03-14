/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Class file for a custom Binary Search Tree node/leaf, 
* serves as a support class for the bst class.
*/

#include "bst_node.h"
#include "identifier.h"
#include <iostream>

using namespace std;

// Custom constructor
bst_node::bst_node(identifier value)
{
	this->id = value;
	this->left = nullptr;
	this->right = nullptr;
}

// Default constructor
bst_node::bst_node()
{
	this->left = nullptr;
	this->right = nullptr;
}

// Destructor
bst_node::~bst_node()
{
	delete left;
	delete right;
}

/*
* Accessor methods
*/

identifier bst_node::get_id()
{
	return this->id;
}

bst_node* bst_node::get_left()
{
	return this->left;
}

bst_node* bst_node::get_right()
{
	return this->right;
}

/*
* Mutator methods
*/

void bst_node::set_id(identifier new_id)
{
	this->id = new_id;
}

void bst_node::set_left(bst_node* new_node)
{
	this->left = new_node;
}

void bst_node::set_right(bst_node* new_node)
{
	this->right = new_node;
}

/*
* Inserts an identifier into the BST.
* 
* Parameters:
* tree: a node representing the entire BST
* new_id: an identifier to be added to the BST
*/
void bst_node::insert(bst_node **tree, identifier new_id)
{
	/*
	* Adds the identifier to the tree, 
	* when the function finds an empty 
	* node and the identifier is a variable, 
	* an array or a function.
	*/
	if (*tree == nullptr)
	{
		if (new_id.id_structure >= 0)
		{
			*tree = new bst_node;
			(*tree)->id = new_id;
			(*tree)->left = nullptr;
			(*tree)->right = nullptr;
		}
	}
	else
	{
		/*
		* If the name and scope of the new identifier 
		* and a stored identifier match, increment the 
		* reference count of the stored identifier.
		*/
		if ((*tree)->id.name.compare(new_id.name) == 0 && ((*tree)->id.scope.compare(new_id.scope) == 0 || (*tree)->id.scope.compare("") == 0))
		{
			(*tree)->id.ref_count++;
		}
		/*
		* Compare the new identifier's name to the 
		* currently analyzed identifier in the BST. If 
		* the first letter of the new identifier's name 
		* comes earlier in the alphabet, than the already 
		* stored identifier's name, call insert on the 
		* left branch. If not, call insert on the right branch.
		*/
		else if ((*tree)->id.name.compare(new_id.name) == 0 || new_id.name.at(0) < (*tree)->id.name.at(0))
		{
			(*tree)->left->bst_node::insert(&(*tree)->left, new_id);
		}
		else if ((*tree)->id.name.compare(new_id.name) == 0 || new_id.name.at(0) >= (*tree)->id.name.at(0))
		{
			(*tree)->right->bst_node::insert(&(*tree)->right, new_id);
		}
	}
}