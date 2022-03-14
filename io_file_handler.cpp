/*
* Author: László Tárkányi
* 
* Last modified: 25/4/2021
* 
* Manages the FILE type pointers.
* Retrieves the code of the input files,
* contains output file logic.
*/

#include "io_file_handler.h"
#include "identifier.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
* Extracts the code from the input file.
* 
* Parameter:
* file_name: the name of the input file
*
* Returns: vector<string> - the lines of the code line by line
*/
vector<string> get_text_from_file(string file_name)
{
	vector<string> lines;
	ifstream file(file_name);
	string line;
	
	// Fill the vector with the lines of the text
	while (getline(file, line))
	{
		lines.push_back(line);
	}
	
	file.close();
	
	return lines;
}

/*
* Tokenises the code from the input file.
* 
* Parameter:
* data: the string vector that contains the lines of the input code
*
* Returns: vector<vector<string>> - tokenised lines (each element contains a line of tokens)
*/
vector<vector<string>> get_tokens_from_data(vector<string> &data)
{
	vector<vector<string>> line_tokens(data.size());
	
	for (int i = 0; i < data.size(); ++i)
	{
		string token;
		stringstream stream(data[i]);
		int token_count_per_line = 0;
		
		// Tokenise each line
		while (stream >> token)
		{
			line_tokens[i].push_back(token);
			token_count_per_line++;
		}
	}
	
	return line_tokens;
}

/*
* Writes all of the identifiers from the input file to an output file.
* 
* Parameter:
* ids: a vector of type identifier
*/
void write_output_file(vector<identifier> &ids)
{
	ofstream file("identifiers.txt");
	
	/*
	* Writes the output file. Each line 
	* corresponds to an identifier. The 
	* output logic is pre-determined.
	*/
	for (int i = 0; i < ids.size(); ++i)
	{
		file << ids[i].name;
		
		if (ids[i].scope != "" && ids[i].scope != "main" && ids[i].id_structure != 2)
		{
			file << " (" << ids[i].scope << ")";
		}
		
		file << ", line " << ids[i].line << ", ";
		
		switch (ids[i].id_structure)
		{
			case 0:
				file << "variable, ";
				break;
			
			case 1:
				file << "array, ";
				break;
			
			case 2:
				file << "function, ";
				break;
		}
		
		file << ids[i].type << ", referenced ";
		
		if (ids[i].ref_count > 0)
		{
			file << ids[i].ref_count - 1 << endl;
		}
		else
		{
			file << ids[i].ref_count << endl;
		}
	}
	
	file.close();
}