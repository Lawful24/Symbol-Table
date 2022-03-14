/*
* Author: László Tárkányi
* 
* Last modified: 24/4/2021
* 
* Contains functions which 
* find and return the number 
* of identifiers of various types.
*/

#include "identifier_counter.h"
#include "identifier.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
* Finds the amount of variables in the code of the input file.
* 
* Parameter:
* ids: a vector of type identifier
*
* Returns: int - the number of variables in the identifiers vector
*/
int get_var_count(vector<identifier> &ids)
{
	int var_count = 0;
	
	if (!ids.empty())
	{
		for (identifier id : ids)
		{
			if (id.id_structure == 0 || id.id_structure == 1)
			{
				var_count++;
			}
		}
	}
	
	return var_count;
}

/*
* Finds the amount of functions in the code of the input file.
* 
* Parameter:
* ids: a vector of identifier values
*
* Returns: int - the number of functions in the identifiers vector
*/
int get_fun_count(vector<identifier> &ids)
{
	int fun_count = 0;
	
	if (!ids.empty())
	{
		for (identifier id : ids)
		{
			if (id.id_structure == 2)
			{
				fun_count++;
			}
		}
	}
	
	return fun_count;
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