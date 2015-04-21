//
//  parser.cpp
//  TinyCompiler
//
//  Created by lms on 12/2/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include "parser.h"
#include "parseError.h"
#include "symbolTable.h"

namespace tinyCompiler{
    Parser::Parser(const std::string &srcfileName):scanner_(Scanner(srcfileName)),symTable_(SymbolTable(tokenSet_)){}
    
    ProgrammAST* Parser::program(){
        nextToken_ = scanner_.getNextToken();
        
        //symTable_.getTable().insert(nextToken_);
        
        if (nextToken_.getTokenType() == TokenType::END_OF_FILE) {
            errorParseMsg(nextToken_, "END OF FILE!");
        }
        
        // damn two lines！
        SeqAST* seqExpr = seq();
        symTable_ = SymbolTable(tokenSet_);
        return new ProgrammAST(&symTable_ ,seqExpr);
    }
    
    SeqAST* Parser::seq(){
        StmtAST* seqLeftStmt = stmt();
        //NopAST* nop = NULL;
        NopAST* nop = new NopAST();
        if ((nextToken_.getTokenType()==TokenType::END_OF_FILE) || (!match(TokenValue::SEMICOLON))) {
                return new SeqAST(seqLeftStmt, nop);
        }
        return new SeqAST(seqLeftStmt, seq());
    }
    
    StmtAST* Parser::stmt(){
        StmtAST* stmt;
        switch (nextToken_.getTokenValue()) {
            case TokenValue::IF :
                stmt = if_stmt();
                break;
                
            case TokenValue::REPEAT :
                stmt = repeat_stmt();
                break;
            case TokenValue::UNRESERVED : //just identifier, not keyword
                stmt = assign_stmt();
                break;
                
            case TokenValue::READ :
                stmt = read_stmt();
                break;
            
            case TokenValue::WRITE :
                stmt = write_stmt();
                break;
            default:
                errorParseMsg(nextToken_, "Serious Error!");
                break;
        }
        
        return stmt;
    }
    
    StmtAST* Parser::if_stmt(){
        if (!match(TokenValue::IF)) {
            errorParseMsg(nextToken_, "No 'IF' here!");
        }
        
        //reduce the logical statement after "IF"
        LogicalAST* logicalExpr = relationStmt();
        
        if (!match(TokenValue::THEN)) {
            errorParseMsg(nextToken_, "No 'THEN' here!");
        }
        
        //reduce "then" statement
        SeqAST* thenStmt = seq();
        bool haveElseStmt= false;
        SeqAST* elseStmt = NULL;
        
        //reduce "else" statement
        if (match(TokenValue::ELSE)) {
            haveElseStmt = true;
            elseStmt = seq();
        }
        
        if (!match(TokenValue::END)) {
            errorParseMsg(nextToken_, "No 'END' here!");
        }
        
        //reduce the whole if_stmt
        StmtAST* ifStmt = NULL;
        if (!haveElseStmt) {
            ifStmt = new IfAST(logicalExpr, thenStmt);
        }
        else{
            ifStmt = new IfElseAST(logicalExpr, thenStmt, elseStmt);
        }
        
        return ifStmt;
    }
    
    StmtAST* Parser::repeat_stmt(){
        if (!match(TokenValue::REPEAT)) {
            errorParseMsg(nextToken_, "Serious Error!");
        }
        
        SeqAST* repeatSeq = seq();
        
        if (!match(TokenValue::UNTIL)) {
            errorParseMsg(nextToken_, "No 'UNTIL' here!");
        }
                          
        LogicalAST* logicalExpr = relationStmt();
                          
        return new RepeatAST(logicalExpr, repeatSeq);
    }
    
    StmtAST* Parser::assign_stmt(){
        idAST* assignId = new idAST(nextToken_);
        //symTable_.getTable().insert(nextToken_);
        tokenSet_.insert(nextToken_);
        
        if (!match(TokenType::IDENTIFIER)){
            errorParseMsg(nextToken_, "Serious Error!");
        }
        
        if (!match(TokenValue::ASSIGN)) {
            errorParseMsg(nextToken_, "No ':=' here!");
        }
        
        ExprAST* assignExpr = expr();
        
        return new AssignAST(assignId, assignExpr);
    }
    
    StmtAST* Parser::read_stmt(){
        if (!match(TokenValue::READ)) {
            errorParseMsg(nextToken_, "Serious Error!");
        }
        
        idAST* readId = new idAST(nextToken_);
        tokenSet_.insert(nextToken_);
        //symTable_.getTable().insert(nextToken_);
        
        if (!match(TokenType::IDENTIFIER)) {
            errorParseMsg(nextToken_, "No 'Identifier' here!");
        }
        
        return new ReadAST(readId);
    }
    
    StmtAST* Parser::write_stmt(){
        if (!match(TokenValue::WRITE)) {
            errorParseMsg(nextToken_, "Serious Error!");
        }
        
        ExprAST *writeExpr = expr();
        
        return new WriteAST(writeExpr);
    }
    
    //eg. a<b, a==b
    LogicalAST* Parser::relationStmt(){
        ExprAST* relationLeftExpr = expr();
        
        Token operatorToken = nextToken_;
        if ((nextToken_.getTokenValue()!=TokenValue::LESS_THAN) &&
            (nextToken_.getTokenValue()!=TokenValue::EQUAL)){
            errorParseMsg(nextToken_, "No '=' or '<' here!");
        }
        
        nextToken_ = scanner_.getNextToken();
        
        ExprAST* relationRightExpr = expr();
        
        return new LogicalAST(operatorToken, relationLeftExpr, relationRightExpr);
    }
    
    
    //eg. a+b,a-b
    ExprAST* Parser::expr(){
        ExprAST* leftExpr = term();
        
        while ((nextToken_.getTokenValue() == TokenValue::PLUS) ||
               (nextToken_.getTokenValue() == TokenValue::MINUS)){
            Token operatorToken = nextToken_;
            nextToken_ = scanner_.getNextToken();
            leftExpr = new ArithAST(operatorToken, leftExpr, term());
        }
        return leftExpr;
    }
    
    //eg. a*b,a/b
    ExprAST* Parser::term(){
        ExprAST* termLeftExpr = factor();
        while ((nextToken_.getTokenValue() == TokenValue::MULTIPLY) ||
               nextToken_.getTokenValue() == TokenValue::DIVIDE) {
            Token operatorToken = nextToken_;
            nextToken_ = scanner_.getNextToken();
            termLeftExpr = new ArithAST(operatorToken, termLeftExpr, term());
        }
        return termLeftExpr;
    }
    
    ExprAST* Parser::factor(){
        ExprAST* factorExpr;
        //nextToken_ = scanner_.getNextToken();
        
        switch (nextToken_.getTokenType()) {
            case TokenType::DELIMITER:
                if (!match(TokenValue::LEFT_PAREN)) {
                    errorParseMsg(nextToken_, "No '(' here!");
                }
                
                factorExpr = expr();
                
                if (!match(TokenValue::RIGTH_PAREN)) {
                    errorParseMsg(nextToken_, "No ')' here!");
                }
                break;
                
            case TokenType::INTERGER:
                factorExpr = new ConstantAST(nextToken_);
                
                
                if (!match(TokenType::INTERGER)) {
                    errorParseMsg(nextToken_, "Serious Error!");
                }
                break;
                
            case TokenType::IDENTIFIER:
                factorExpr = new idAST(nextToken_);
                /*if(symTable_->getTable().find(nextToken_) != symTable_->getTable().end()){
                    factorExpr = new idAST(nextToken_);
                }
                 */
                
                if (!match(TokenType::IDENTIFIER)) {
                    errorParseMsg(nextToken_, "Serious Error!");
                }
                break;
                
            default:
                errorParseMsg(nextToken_, "Serious Error!");
                break;
        }
        return factorExpr;
    }
    
    bool Parser::match(const TokenType &tokenType){
        if (nextToken_.getTokenType() == tokenType) {
            nextToken_ = scanner_.getNextToken();
            return true;
        }
        return false;
    }
    
    bool Parser::match(const TokenValue &tokenValue){
        if (nextToken_.getTokenValue() == tokenValue) {
            nextToken_ = scanner_.getNextToken();
            return true;
        }
        
        return false;
    }
    
}
