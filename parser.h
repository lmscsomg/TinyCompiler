//
//  parser.h
//  TinyCompiler
//
//  Created by lms on 12/2/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#ifndef __TinyCompiler__parser__
#define __TinyCompiler__parser__

#include <iostream>
#include "scanner.h"
#include "token.h"
#include "ast.h"

namespace tinyCompiler{
    class Parser{
    public:
        Parser(const std::string &srcFileName);
        ProgrammAST*    program();
        Scanner getScanner(const std::string &srcfileName) const;
        
    private:
        bool    match(const TokenValue &tokenValue);
        bool    match(const TokenType &tokenType);
        
        SeqAST*     seq();
        StmtAST*    stmt();
        StmtAST*    if_stmt();
        StmtAST*    repeat_stmt();
        StmtAST*    assign_stmt();
        StmtAST*    read_stmt();
        StmtAST*    write_stmt();
        LogicalAST* relationStmt();
        ExprAST*    term();
        ExprAST*    expr();
        ExprAST*    factor();
        
    private:
        Scanner         scanner_;
        Token           nextToken_;
        std::set<Token> tokenSet_;
        SymbolTable     symTable_;
    };
    
    inline Scanner Parser::getScanner(const std::string &srcfileName) const{
        return Scanner(srcfileName);
    }
}

#endif /* defined(__TinyCompiler__parser__) */
