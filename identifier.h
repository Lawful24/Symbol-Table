/*
* Author: László Tárkányi
* 
* Last modified: 23/4/2021
* 
* Header file for identifier.cpp.
*/

#pragma once

#include <string>

struct identifier
{
	std::string name;
	int line;
	
	/* The variable id_structure indicates 
	* whether a particular identifier 
	* represents a variable (0), 
	* an array (1), or a function (2).
	*/
	int id_structure;
	std::string type;
	int ref_count;
	std::string scope;
};