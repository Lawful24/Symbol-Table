/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Contains functions which 
* find and return the number 
* of identifiers of various types.
*/

#include "identifier_counter_b.h"
#include "identifier.h"
#include "bst_node.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
* Adds the variables and arrays up recursively.
* 
* Parameter:
* root: the first node of the BST containing the identifiers
*
* Returns: int - the sum of the variable and array count in the left and right branches
*/
int get_var_count(bst_node *root)
{
	if (root == nullptr)
	{
		return 0;	
	}

	if (root->get_id().id_structure == 0 || root->get_id().id_structure == 1)
	{
		return 1 + get_var_count(root->get_left()) + get_var_count(root->get_right());
	}

	return 0 + get_var_count(root->get_left()) + get_var_count(root->get_right());

}

/*
* Adds the functions up recursively.
* 
* Parameter:
* root: the first node of the BST containing the identifiers
*
* Returns: int - the sum of the function count in the left and right branches
*/
int get_fun_count(bst_node *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	
	if (root->get_id().id_structure == 2)
	{
		return 1 + get_fun_count(root->get_left()) + get_fun_count(root->get_right());
	}
	
	return 0 + get_fun_count(root->get_left()) + get_fun_count(root->get_right());
}

/*
* Finds the amount of if statements in the code of the input file.
* 
* Parameter:
* tokens: a vector of vectors of string values, containing lines of tokens from the input code
*
* Returns: int - the number if statements in the tokens vector
*/
int get_if_count(vector<vector<string>> &tokens)
{
	int if_count = 0;
	
	if (!tokens.empty())
	{
		// Loop through the tokenised lines of the vector
		for (int i = 0; i < tokens.size(); ++i)
		{
			// Loop through the tokens of each line
			for (int j = 0; j < tokens[i].size(); ++j)
			{
				if (tokens[i][j].compare("if") == 0)
				{
					if_count++;
				}
			}
		}
	}
	
	return if_count;
}

/*
* Finds the amount of for loops in the code of the input file.
* 
* Parameter:
* tokens: a vector of vectors of string values, containing lines of tokens from the input code
*
* Returns: int - the number for loops in the tokens vector
*/
int get_for_count(vector<vector<string>> &tokens)
{
	int for_count = 0;
	
	if (!tokens.empty())
	{
		// Loop through the tokenised lines of the vector
		for (int i = 0; i < tokens.size(); ++i)
		{
			// Loop through the tokens of each line
			for (int j = 0; j < tokens[i].size(); ++j)
			{
				if (tokens[i][j].compare("for") == 0)
				{
					for_count++;
				}
			}
		}
	}
	
	return for_count;
}

/*
* Finds the amount of while loops in the code of the input file.
* 
* Parameter:
* tokens: a vector of vectors of string values, containing lines of tokens from the input code
*
* Returns: int - the number while loops in the tokens vector
*/
int get_while_count(vector<vector<string>> &tokens)
{
	int while_count = 0;
	
	if (!tokens.empty())
	{
		// Loop through the tokenised lines of the vector
		for (int i = 0; i < tokens.size(); ++i)
		{
			// Loop through the tokens of each line
			for (int j = 0; j < tokens[i].size(); ++j)
			{
				if (tokens[i][j].compare("while") == 0)
				{
					while_count++;
				}
			}
		}
	}
	
	return while_count;
}