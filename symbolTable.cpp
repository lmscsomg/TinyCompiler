//
//  symbolTable.cpp
//  tc
//
//  Created by lms on 12/9/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include "symbolTable.h"
#include "token.h"
namespace tinyCompiler {
    std::string SymbolTable::toString(){
        std::string str = "int ";
        bool isFirstOne = true;
        for (auto token : table_) {
            if (isFirstOne) {
                str += token.getTokenName();
                isFirstOne = false;
            }
            else{
                str += ", ";
                str += token.getTokenName();
            }
        }
        str.append(";");
        return str;
    }
}