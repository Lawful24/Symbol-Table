/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* The purpose of this file is to find 
* variables and functions in the input 
* file, then store these as identifier 
* structs in a vector.
*/

#include "identifier_finder.h"
#include "identifier.h"
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
* ids: a vector of type identifier, to be filled with identifier values
*/
void populate_ids_vector(vector<vector<string>> &tokens, vector<identifier> &ids)
{
	int id_count = 0;
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
								* Stores the newly found array in the identifier vector ids.
								*/
								ids.push_back(identifier());
								set_identifier_values(ids[id_count], tokens[i][j + 2], i + 1, 1, tokens[i][j] + " " + tokens[i][j + 1]);
								
								if (!function_stack.empty())
								{
									ids[id_count].scope = function_stack[function_stack.size() - 1];
								}
								
								/*
								* If the identifier was declared in the most outer scope, 
								* the scope of the identifier remains the default value, 
								* which is an empty string.
								*/
								
								id_count++; // increment count to keep track of the number of identifiers found
							}
							else
							{
								/*
								* Stores the newly found variable in the identifier vector ids.
								*/
								ids.push_back(identifier());
								set_identifier_values(ids[id_count], tokens[i][j + 2], i + 1, 0, tokens[i][j] + " " + tokens[i][j + 1]);
								
								if (!function_stack.empty())
								{
									ids[id_count].scope = function_stack[function_stack.size() - 1];
								}
								
								id_count++;
							}
						}
						else // function signature found
						{
							/*
							* Stores the newly found function in the identifier vector ids.
							*/
							ids.push_back(identifier());
							set_identifier_values(ids[id_count], tokens[i][j + 2], i + 1, 2, tokens[i][j] + " " + tokens[i][j + 1]);
							
							if (!function_stack.empty())
							{
								ids[id_count].scope = function_stack[function_stack.size() - 1];
							}
							
							id_count++;
							
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
								// Check for an array declaration by looking for an opening square bracket
								if (tokens[i][j + 2].find("[") != string::npos)
								{
									/*
									* Stores the newly found array in the identifier vector ids.
									*/
									ids.push_back(identifier());
									set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 1, tokens[i][j]);
									
									if (!function_stack.empty())
									{
										ids[id_count].scope = function_stack[function_stack.size() - 1];
									}
									
									id_count++;
								}
								else // function signature found
								{
									/*
									* Stores the newly found variable in the identifier vector ids.
									*/
									ids.push_back(identifier());
									set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 0, tokens[i][j]);
									
									if (!function_stack.empty())
									{
										ids[id_count].scope = function_stack[function_stack.size() - 1];
									}
									
									id_count++;
								}
							}
							else
							{
								/*
								* Stores the newly found function in the identifier vector ids.
								*/
								ids.push_back(identifier());
								set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 2, tokens[i][j]);
								
								if (!function_stack.empty())
								{
									ids[id_count].scope = function_stack[function_stack.size() - 1];
								}
								
								id_count++;
								
								function_stack.push_back(tokens[i][j + 1]);
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
						// Check for an array declaration by looking for an opening square bracket
						if (tokens[i][j + 2].find("[") != string::npos)
						{
							/*
							* Stores the newly found array in the identifier vector ids.
							*/
							ids.push_back(identifier());
							set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 1, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								ids[id_count].scope = function_stack[function_stack.size() - 1];
							}
							
							id_count++;
						}
						else
						{
							/*
							* Stores the newly found variable in the identifier vector ids.
							*/
							ids.push_back(identifier());
							set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 0, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								ids[id_count].scope = function_stack[function_stack.size() - 1];
							}
							
							id_count++;
						}
					}
					else // function signature found
					{
						/*
						* Stores the newly found function in the identifier vector ids.
						*/
						ids.push_back(identifier());
						set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 2, tokens[i][j]);
						
						if (!function_stack.empty())
						{
							ids[id_count].scope = function_stack[function_stack.size() - 1];
						}
						
						id_count++;
						
						// function scope started
						function_stack.push_back(tokens[i][j + 1]);
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
						// Check for an array declaration by looking for an opening square bracket
						if (tokens[i][j + 2].find("[") != string::npos)
						{
							/*
							* Stores the newly found array in the identifier vector ids.
							*/
							ids.push_back(identifier());
							set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 1, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								ids[id_count].scope = function_stack[function_stack.size() - 1];
							}
							
							id_count++;
						}
						else
						{
							/*
							* Stores the newly found variable in the identifier vector ids.
							*/
							ids.push_back(identifier());
							set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 0, tokens[i][j]);
							
							if (!function_stack.empty())
							{
								ids[id_count].scope = function_stack[function_stack.size() - 1];
							}
							
							id_count++;
						}
					}
					else // function signature found
					{
						/*
						* Stores the newly found function in the identifier vector ids.
						*/
						ids.push_back(identifier());
						set_identifier_values(ids[id_count], tokens[i][j + 1], i + 1, 2, tokens[i][j]);
						
						if (!function_stack.empty())
						{
							ids[id_count].scope = function_stack[function_stack.size() - 1];
						}
						
						id_count++;
						
						function_stack.push_back(tokens[i][j + 1]);
					}
				}
			}
			
			/*
			* Increments the reference count of an identifier if
			* it is referred in the code of the input file.
			*/
			for (int k = 0; k < ids.size(); ++k)
			{
				// Check if the name of the currently analyzed identifier is the same as the currently analized token
				if (ids[k].name.compare(tokens[i][j]) == 0 && !function_stack.empty())
				{
					// Loop through the current function stack
					for (int l = 0; l < function_stack.size(); ++l)
					{
						// Check if the element was declared in an earler or the current function scope
						if (ids[k].scope.compare(function_stack[l]) == 0)
						{
							ids[k].ref_count++;
						}
					}
					
					// Check if the element was declared outside of all functions
					if (ids[k].scope.compare("") == 0)
					{
						ids[k].ref_count++;
					}
				}
				// Check if the element was declared with the function stack being empty
				else if (ids[k].name.compare(tokens[i][j]) == 0)
				{
					ids[k].ref_count++;
				}
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