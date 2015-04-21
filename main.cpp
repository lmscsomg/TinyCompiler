//
//  main.cpp
//  TinyCompiler
//
//  Created by lms on 12/8/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include "parser.h"
using namespace tinyCompiler;

int main()
{
    Parser myParser("/Users/lms/Documents/TinyCompiler/TinyCompiler/test.txt");
    
    Scanner myScanner = myParser.getScanner("/Users/lms/Documents/TinyCompiler/TinyCompiler/test.txt");
    
    do{
        myScanner.getNextToken();
        myScanner.getToken().dump();
        
    }while (myScanner.getToken().getTokenType() != TokenType::END_OF_FILE);

    std::cout << std::endl << std::endl;
    ProgrammAST *program = myParser.program();
    //SymbolTable *a = NULL;
    program->dump(0, std::cout);
    std::cout << std::endl << std::endl;
    //program->gen(std::cout);
    
    //std::cout << std::endl << std::endl;
    //program->trans_to_json(0, std::cout);
    
    std::cout << std::endl << std::endl;
    program->gen(std::cout);

    return 0;
}