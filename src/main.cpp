#include <iostream>
#include <string.h>
#include <main.h>

using namespace std;
int main(int argc, char *argv[]){
       if(!strcmp(argv[1], "scan")) {
        g_tokens = 1;
        while(yylex());
        cout << "OK" << endl;
        return 0;
    }
    else if(!strcmp(argv[1], "tokens")) {
	g_tokens = 1;
        while(yylex());
        return 0;
    }
    else if(!strcmp(argv[1], "parse")) {
        yyparse();
        cout << "OK" << endl;
        return 0;
    }
    else if(!strcmp(argv[1], "pretty")) {
        yyparse();
      //   prettyINS(rootIns, 0);
        cout << "OK" << endl;
        return 0;
    }
}
