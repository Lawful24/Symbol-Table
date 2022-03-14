/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* The purpose of this file is to find 
* variables and functions in the input 
* file, then store these as identifier 
* structs in a Binary Search Tree.
*/

#include "identifier_finder_b.h"
#include "identifier.h"
#include "bst.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
* Sets the values of an identifier.
* 
* Parameters:
* id: the identifier to be edited
* name: the new name of the identifier
* line: the number of the line where the identifier was located
* id_structure: an int value that determines the kind of the identifier
* type: a value representing the type of the identifier variable or function
*/
void set_identifier_values(identifier &id, string name, int line, int id_structure, string type)
{
	id.name = name;
	id.line = line;
	id.id_structure = id_structure;
	id.type = type;
}

/*
* Analyzes the code from the input file. Recognises C declaration patterns and 
* function signatures to store them in an identifier vector.
* 
* Parameters:
* tokens: a vector of vectors of string values, containing lines of tokens from the input code
* tree: a Binary Search Tree to be filled with identifier struct values
*/
void populate_identifier_tree(vector<vector<string>> &tokens, bst *tree)
{
	vector<string> function_stack; // declare a vector to keep track of where each variable was declared
	
	// Loop through the tokenised lines of the vector
	for (int i = 0; i < tokens.size(); ++i)
	{
		// Loop through the tokens of each line
		for (int j = 0; j < tokens[i].size(); ++j)
		{
			// Check whether the token is a data type or not
			if (tokens[i][j].compare("char") == 0 || tokens[i][j].compare("short") == 0
			|| tokens[i][j].compare("int") == 0 || tokens[i][j].compare("long") == 0
			|| tokens[i][j].compare("float") == 0 || tokens[i][j].compare("double") == 0
			|| tokens[i][j].compare("void") == 0)
			{
				// Check for long long data type by analyzing the next token in the line
				if (j + 1 < tokens[i].size() && tokens[i][j].compare("long") == 0
				&& (tokens[i][j + 1].compare("long") == 0
				|| tokens[i][j + 1].compare("long*") == 0
				|| tokens[i][j + 1].compare("long**") == 0))
				{
					/*
					* An offset of 2 is added to the current index j, 
					* to find the name of an identifier of a long long type.
					*/
					if (j + 2 < tokens[i].size())
					{
						// Check for function signature by looking for an opening paranthesis
						if (tokens[i][j + 2].compare("(") != 0)
						{
							// Check for an array declaration by looking for an opening square bracket
							if (tokens[i][j + 2].find("[") != string::npos)
							{
								/*
								* Stores the newly found array in the BST.
								*/
								identifier id = identifier();
								set_identifier_values(id, tokens[i][j + 2], i + 1, 1, tokens[i][j] + " " + tokens[i][j + 1]);
								
								if (!function_stack.empty())
								{
									id.scope = function_stack.back();
								}
								
								/*
								* If the identifier was declared in the most outer scope, 
								* the scope of the identifier remains the default value, 
								* which is an empty string.
								*/
								
								tree->update(id); // insert the new identifier into the BST
							}
							else // non-array variable declaration found
							{
								/*
								* Stores the newly found variable in the BST.
								*/
								identifier id = identifier();
								set_identifier_values(id, tokens[i][j + 2], i + 1, 0, tokens[i][j] + " " + tokens[i][j + 1]);
								
								if (!function_stack.empty())
								{
									id.scope = function_stack.back();
								}
								
								tree->update(id);
							}
						}
						else // function signature found
						{
							/*
							* Stores the newly found function in the BST.
							*/
							identifier id = identifier();
							set_identifier_values(id, tokens[i][j + 2], i + 1, 2, tokens[i][j] + " " + tokens[i][j + 1]);
							
							if (!function_stack.empty())
							{
								id.scope = function_stack.back();
							}
							
							tree->update(id);
							
							function_stack.push_back(tokens[i][j + 2]); // mark the start of the current function scope
						}
					}
				}
				else // a case where the identifier is not a long long
				{
					if (!(j - 1 >= 0 && tokens[i][j - 1].compare("long") == 0))
					{
						if (j + 2 < tokens[i].size())
						{
							// Check for function signature by looking for an opening paranthesis
							if (tokens[i][j + 2].compare("(") != 0)
							{
								if (tokens[i][j + 2].find("[") != string::npos)
								{
									/*
									* Stores the newly found array in the BST.
									*/
									identifier id = identifier();
									set_identifier_values(id, tokens[i][j + 1], i + 1, 1, tokens[i][j]);
									
									if (!function_stack.empty())
									{
										id.scope = function_stack.back();
									}
									
									tree->update(id);
								}
								else // non-array variable declaration found
								{
									/*
									* Stores the newly found variable in the BST.
									*/
									identifier id = identifier();
									set_identifier_values(id, tokens[i][j + 1], i + 1, 0, tokens[i][j]);
									
									if (!function_stack.empty())
									{
										id.scope = function_stack.back();
									}
									
									tree->update(id);
								}
							}
							else // function signature found
							{
								/*
								* Stores the newly found function in the BST.
								*/
								identifier id = identifier();
								set_identifier_values(id, tokens[i][j + 1], i + 1, 2, tokens[i][j]);
								
								if (!function_stack.empty())
								{
									id.scope = function_stack.back();
								}
								
								tree->update(id);
								
								function_stack.push_back(tokens[i][j + 1]); // mark the start of the current function scope
							}
						}
					}
				}
			}
			
			// Check whether the token is a pointer-to-data type or not
			if (tokens[i][j].compare("char*") == 0 || tokens[i][j].compare("short*") == 0
			|| tokens[i][j].compare("int*") == 0 || tokens[i][j].compare("long*") == 0
			|| tokens[i][j].compare("float*") == 0 || tokens[i][j].compare("double*") == 0
			|| tokens[i][j].compare("void*") == 0)
			{
				if (j + 2 < tokens[i].size())
				{
					// Check for function signature by looking for an opening paranthesis
					if (tokens[i][j + 2].compare("(") != 0)
					{
						if (tokens[i][j + 2].find("[") != string::npos)
						{
							/*
							* Stores the newly found array in the BST.
							*/
							identifier id = identifier();
							set_identifier_values(id, tokens[i][j + 1], i + 1, 1, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								id.scope = function_stack.back();
							}
							
							tree->update(id);
						}
						else // non-array variable declaration found
						{
							/*
							* Stores the newly found variable in the BST.
							*/
							identifier id = identifier();
							set_identifier_values(id, tokens[i][j + 1], i + 1, 0, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								id.scope = function_stack.back();
							}
							
							tree->update(id);
						}
					}
					else // function signature found
					{
						/*
						* Stores the newly found function in the BST.
						*/
						identifier id = identifier();
						set_identifier_values(id, tokens[i][j + 1], i + 1, 2, tokens[i][j]);
						
						if (!function_stack.empty())
						{
							id.scope = function_stack.back();
						}
						
						tree->update(id);
						
						function_stack.push_back(tokens[i][j + 1]); // mark the start of the current function scope
					}
				}
			}
			
			// Check whether the token is a pointer-to-pointer-to-data type or not
			if (tokens[i][j].compare("char**") == 0 || tokens[i][j].compare("short**") == 0
			|| tokens[i][j].compare("int**") == 0 || tokens[i][j].compare("long**") == 0
			|| tokens[i][j].compare("float**") == 0 || tokens[i][j].compare("double**") == 0
			|| tokens[i][j].compare("void**") == 0)
			{
				if (j + 2 < tokens[i].size())
				{
					// Check for function signature by looking for an opening paranthesis
					if (tokens[i][j + 2].compare("(") != 0)
					{
						if (tokens[i][j + 2].find("[") != string::npos)
						{
							/*
							* Stores the newly found array in the BST.
							*/
							identifier id = identifier();
							set_identifier_values(id, tokens[i][j + 1], i + 1, 1, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								id.scope = function_stack.back();
							}
							
							tree->update(id);
						}
						else // non-array variable declaration found
						{
							/*
							* Stores the newly found variable in the BST.
							*/
							identifier id = identifier();
							set_identifier_values(id, tokens[i][j + 1], i + 1, 0, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								id.scope = function_stack.back();
							}
							
							tree->update(id);
						}
					}
					else // function signature found
					{
						/*
						* Stores the newly found function in the BST.
						*/
						identifier id = identifier();
						set_identifier_values(id, tokens[i][j + 1], i + 1, 2, tokens[i][j]);
						
						if (!function_stack.empty())
						{
							id.scope = function_stack.back();
						}
						
						tree->update(id);
						
						function_stack.push_back(tokens[i][j + 1]); // mark the start of the current function scope
					}
				}
			}
			
			/*
			* Increments the reference count of the identifier
			* that matches the name of the current token. We 
			* create a new identifier with the purpose of incrementing 
			* the reference count of the matching identifier 
			* in the BST, not for inserting a new identifier.
			*/
			if (tree->contains(tree->get_root(), tokens[i][j]))
			{
				identifier ref_incrementer = identifier();
				ref_incrementer.name = tokens[i][j];
				ref_incrementer.id_structure = -1; // distinct mark of identifier references in C code
				
				if (!function_stack.empty())
				{
					ref_incrementer.scope = function_stack.back();
				}
				
				tree->update(ref_incrementer);
			}
			
			/*
			* Updates the function stack whenever we encounter a "}" character
			*/
			if (!function_stack.empty() && tokens[i][j].compare("}") == 0)
			{
				// Assign the indeces of the "}" character from the tokens array
				int line_index = i;
				int token_index = j;
				
				// Loop through the tokens backwards, until the beginning of the code or until the "{" character is found
				do
				{
					if (tokens[line_index][token_index].compare("{") == 0)
					{
						break; // exit this loop when we encounter a "{" character
					}
					
					// Step to the previous token
					// If token_index reached to the beginning of a line, step to the previous line
					if (token_index == 0 && line_index > 0)
					{
						line_index--;
						
						if (!tokens[line_index].empty())
						{
							token_index = tokens[line_index].size();
						}
					}
					
					token_index--;
				}
				while (line_index >= 0 && tokens[line_index][token_index].compare("{") != 0);
				
				/*
				* The variables line_index and token_index now collectively 
				* contain the coordinates of the first "{" found in the code.
				*/
				
				// Loop through the tokens backwards, until the beginning of the code or until the function's name is found
				do
				{
					// Step to the previous token
					// If token_index reached to the beginning of a line, step to the previous line
					if (token_index <= 0 && line_index > 0)
					{
						line_index--;
						
						if (!tokens[line_index].empty())
						{
							token_index = tokens[line_index].size();
						}
					}
					
					token_index--;
					
					/*
					* The next if statement is required to distinguish the if 
					* statements, loops and lambda structures and other scopes 
					* from the function scopes. The purpose of this code fragment 
					* is to find the end of a function scope.
					*/
					
					// Determine if the token found in front of the "{" character matches the element in the function stack
					if (tokens[line_index][token_index].compare(function_stack.back()) == 0)
					{
						function_stack.pop_back(); // pop the last function added to the stack
					}
				}
				while (line_index >= 0 && !function_stack.empty() && tokens[line_index][token_index].compare(function_stack.back()) != 0);
			}
		}
	}
}