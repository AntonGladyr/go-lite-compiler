#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <string.h>
#include "main.hpp"

void printUsageInfo() {	
	std::cerr << "Usage: ./build/bin/golite/ <mode> [<filename>]\n"
	<< " + mode: scan|tokens|parse|pretty|symbol|typecheck|codegen\n";
}

int main(int argc, char *argv[]){

	// Number of args - 3 (name of the program, mode, file)
	if (argc != 2) {
		std::cerr << "Error: Invalid number of arguments\n";
		printUsageInfo();
		return 1;
	}


	if(!strcmp(argv[1], "scan")) {
        	g_tokens = 0;
        	while(yylex());	
        	std::cout << "OK" << std::endl;
        	return 0;
    	}
    	else if(!strcmp(argv[1], "tokens")) {
		g_tokens = 1;
        	while(yylex());
        	return 0;
    	}
    	else if(!strcmp(argv[1], "parse")) {
        	yyparse();
        	std::cout << "OK" << std::endl;
		
		delete program;
		program = NULL;
        	return 0;
    	}
    	else if(!strcmp(argv[1], "pretty")) {		
        	yyparse();
		PrettyPrinter printer;	
		ASTTraversal::traverse(program, printer);	
		
		delete program;
		program = NULL;
        	return 0;
    	}
	else if(!strcmp(argv[1], "symbol")) {
		yyparse();
		SymbolTableBuilder builder;
		symbolTable = builder.build(program);
		std::cout << symbolTable->toString();	
		
		delete symbolTable;
		symbolTable = NULL;
		delete program;
		program = NULL;
		return 0;
	}
	else if(!strcmp(argv[1], "typecheck")) {
		yyparse();
		SymbolTableBuilder builder;
		symbolTable = builder.build(program);
		TypeChecker checker;
		checker.typecheck(program, symbolTable);		
			
		std::cout << "OK" << std::endl;
		delete program;
		program = NULL;
		delete symbolTable;
		symbolTable = NULL;
		return 0;
	}
	else {	
		std::cerr << "Error: Unknown mode \"" << argv[1] << "\"" << std::endl;
		printUsageInfo();
		return 1;
	}
}

#endif
