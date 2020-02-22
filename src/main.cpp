#include <iostream>
#include <string.h>
#include <main.h>

void yyparse();
int yylex();

int main(int argc, char *argv[]){
       if(!strcmp(argv[1], "scan")) {
        g_tokens = 1;
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
        return 0;
    }
    else if(!strcmp(argv[1], "pretty")) {
        yyparse();
      //   prettyInstruction(rootIns, 0);
        std::cout << "OK" << std::endl;
        return 0;
    }
}
