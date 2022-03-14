/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Part A of the symbol_table application.
* The purpose of this program is to scan
* C language files and collect information
* about variables and functions declared 
* in the source file. This information is
* also printed to the console and written
* to an external file (identifiers.txt).
* 
* This is the main file for Part A
* of the symble_table application.
*/

#include "identifier.h"
#include "identifier_finder.h"
#include "identifier_counter.h"
#include "io_file_handler.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		// Store text from input file in vectors
		vector<string> data = get_text_from_file(argv[1]);
		vector<vector<string>> tokens = get_tokens_from_data(data);
		
		// Store identifiers in another vector
		vector<identifier> ids;
		populate_ids_vector(tokens, ids);
		
		// Print source code details
		cout << "\nVariables: " << get_var_count(ids) << endl;
		cout << "Functions: " << get_fun_count(ids) << endl;
		cout << "If statements: " << get_if_count(tokens) << endl;
		cout << "For loops: " << get_for_count(tokens) << endl;
		cout << "While loops: " << get_while_count(tokens) << endl;
		
		// Create output file
		write_output_file(ids);
	}
	else
	{
		cout << "Error: An incorrect number of arguments were provided. (correct format: symbol_table your_file_name_here.c)" << endl;
	}
	
	return 0;
}