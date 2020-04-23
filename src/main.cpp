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


	if (!strcmp(argv[1], "scan")) {
        	g_tokens = 0;
        	while (yylex());	
        	std::cout << "OK" << std::endl;
        	return 0;
    	}
    	else if (!strcmp(argv[1], "tokens")) {
		g_tokens = 1;
        	while (yylex());
        	return 0;
    	}
    	else if (!strcmp(argv[1], "parse")) {
        	yyparse();
        	std::cout << "OK" << std::endl;
		
		delete program;
		program = NULL;
        	return 0;
    	}
    	else if (!strcmp(argv[1], "pretty")) {		
        	yyparse();
		PrettyPrinter printer;	
		ASTTraversal::traverse(program, printer);	
		
		delete program;
		program = NULL;
        	return 0;
    	}
	else if (!strcmp(argv[1], "symbol")) {
		yyparse();	
		SymbolTable *symbolTable = new SymbolTable(program, true);	
		std::cout << symbolTable->toString();
		
		//TODO: invoke deallocate() behind the scenes
		symbolTable->deallocate();
		delete symbolTable;
		symbolTable = NULL;
		delete program;
		program = NULL;
		return 0;
	}
	else if (!strcmp(argv[1], "typecheck")) {
		yyparse();	
		SymbolTable *symbolTable = new SymbolTable(program);
		
		std::cout << "OK" << std::endl;
			
		//TODO: invoke deallocate() behind the scenes
		symbolTable->deallocate();
		delete symbolTable;	
		delete program;
		program = NULL;
		symbolTable = NULL;
		return 0;
	}
	else if (!strcmp(argv[1], "codegen")) {
		yyparse();
		SymbolTable *symbolTable = new SymbolTable(program);
		CodeGenerator codeGen;
			
		codeGen.emit(program, symbolTable);
		
		std::cout << "OK" << std::endl;
		
		//TODO: invoke deallocate() behind the scenes
		symbolTable->deallocate();
		delete symbolTable;	
		delete program;
		program = NULL;
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
