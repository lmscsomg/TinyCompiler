//
//  symbolTable.h
//  tc
//
//  Created by lms on 12/9/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#ifndef __tc__symbolTable__
#define __tc__symbolTable__

#include <set>
#include <vector>
#include "token.h"
namespace tinyCompiler {
    class SymbolTable{
    public:
        SymbolTable(std::set<Token> table):table_(table){}
        std::string toString();
        std::set<Token> getTable(){
            return this->table_;
        }
        
    private:
        std::set<Token> table_;
    };
}

#endif /* defined(__tc__symbolTable__) */
