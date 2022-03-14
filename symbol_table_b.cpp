/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Part B of the symbol_table application.
* The purpose of this program is to scan
* C language files and collect information
* about variables and functions declared 
* in the source file. This information is
* also printed to the console and written
* to an external file (identifiers.txt).
* 
* Part B uses a Binary Search Tree to 
* store the identifiers for increased 
* effectiveness.
* 
* This is the main file for Part B
* of the symble_table application.
*/

#include "bst_node.h"
#include "bst.h"
#include "identifier.h"
#include "identifier_counter_b.h"
#include "identifier_finder_b.h"
#include "io_file_handler_b.h"
#include <iostream>
#include <fstream>
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
		
		// Store the identifiers in the Binary Search Tree
		bst *tree = new bst;
		populate_identifier_tree(tokens, tree);
		
		// Print source code details
		cout << "\nVariables: " << get_var_count(tree->get_root()) << endl;
		cout << "Functions: " << get_fun_count(tree->get_root()) << endl;
		cout << "If statements: " << get_if_count(tokens) << endl;
		cout << "For loops: " << get_for_count(tokens) << endl;
		cout << "While loops: " << get_while_count(tokens) << endl << endl;
		
		// Print all identifiers to the console
		tree->print_table(tree->get_root());
		
		// Create output file
		ofstream file("identifiers.txt");
		write_output_file(tree->get_root(), file);
		file.close();
		
		delete tree;
	}
	else
	{
		cout << "Error: An incorrect number of arguments were provided. (correct format: symbol_table_b your_file_name_here.c)" << endl;
	}
	
	return 0;
}