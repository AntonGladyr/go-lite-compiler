#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <string.h>
#include "main.hpp"

int main(int argc, char *argv[]){
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
		
		ASTTraversal::clean(program);
        	return 0;
    	}
    	else if(!strcmp(argv[1], "pretty")) {		
        	yyparse();
		PrettyPrinter printer;
		ASTTraversal::traverse(program, printer);	
		
		ASTTraversal::clean(program);	
        	return 0;
    	}
}

#endif
