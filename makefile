all: symbol_table symbol_table_b

symbol_table:
	cl /EHsc /c symbol_table.cpp identifier.cpp identifier_counter.cpp identifier_finder.cpp io_file_handler.cpp
	lib /OUT:analyser.lib identifier.obj identifier_counter.obj identifier_finder.obj io_file_handler.obj
	link symbol_table.obj analyser.lib
	
symbol_table_b:
	cl /EHsc /c symbol_table_b.cpp bst.cpp bst_node.cpp identifier.cpp identifier_counter_b.cpp identifier_finder_b.cpp io_file_handler_b.cpp
	lib /OUT:binary_search_tree.lib bst.obj bst_node.obj
	lib /OUT:analyser_b.lib identifier.obj identifier_counter_b.obj identifier_finder_b.obj io_file_handler_b.obj
	link symbol_table_b.obj binary_search_tree.lib analyser_b.lib
	
clean:
	del *.obj
	del *.lib
	del *.exe
	del *.txt