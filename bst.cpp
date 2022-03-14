/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Class file for a custom Binary Search Tree, 
* intended to store identifier struct values.
*/

#include "bst.h"
#include "bst_node.h"
#include "identifier.h"
#include <iostream>
#include <string>

using namespace std;

// Default constructor
bst::bst()
{
	this->root = nullptr;
}

// Destructor
bst::~bst()
{
	delete root;
}

/*
* Accessor method
*/
bst_node* bst::get_root()
{
	return this->root;
}

/*
* Update the BST with a new identifier. 
* If the parameter identifier is identical 
* to an identifier already stored in 
* the BST, the reference count of the 
* already stored identifier gets incremented.
* 
* Parameter:
* new_id: an identifier from the input code
*/
void bst::update(identifier new_id)
{
	if (this->root == nullptr)
	{
		this->root = new bst_node;
		this->root->set_id(new_id);
		this->root->set_left(nullptr);
		this->root->set_right(nullptr);
	}
	else
	{
		this->root->insert(&(*this).root, new_id);
	}
}

/*
* Determines whether the parameter identifier 
* is already stored in the BST or not.
* 
* Parameters:
* node: a leaf of the BST
* key: the search value, an identifier name
*
* Returns: bool - the tree contains the search element or not
*/
bool bst::contains(bst_node* node, string key)
{
	if (node == nullptr)
	{
		return false;
	}
	else
	{
		if (node->get_id().name.compare(key) == 0)
		{
			return true;
		}
		else if (key.at(0) < node->get_id().name.at(0)) // alphabetical comparison
		{
			return contains(node->get_left(), key);
		}
		else if (key.at(0) >= node->get_id().name.at(0)) // alphabetical comparison
		{
			return contains(node->get_right(), key);
		}
		else
		{
			return false;
		}
	}
}

/*
* Writes all of the identifiers from the input 
* file to the console in alphabetical order.
* 
* Parameter:
* node: a leaf of the BST
*/
void bst::print_table(bst_node *node)
{
	if (node != nullptr)
	{
		// Inorder traversal, beginning with the left branch
		bst::print_table(node->get_left());
		
		/*
		* Writes the output file. Each line 
		* corresponds to an identifier. The 
		* output logic is pre-determined.
		*/
		cout << node->get_id().name;
	
		if (node->get_id().scope != "" && node->get_id().scope != "main" && node->get_id().id_structure != 2)
		{
			cout << " (" << node->get_id().scope << ")";
		}
		
		cout << ", line " << node->get_id().line << ", ";
		
		switch (node->get_id().id_structure)
		{
			case 0:
				cout << "variable, ";
				break;
			
			case 1:
				cout << "array, ";
				break;
			
			case 2:
				cout << "function, ";
				break;
		}
		
		cout << node->get_id().type << ", referenced ";
		
		if (node->get_id().ref_count > 0)
		{
			cout << node->get_id().ref_count - 1 << endl;
		}
		else
		{
			cout << node->get_id().ref_count << endl;
		}
		
		// Inorder traversal, ending with the right branch
		bst::print_table(node->get_right());
	}
}