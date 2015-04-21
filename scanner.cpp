//
//  scanner.cpp
//  TinyCompiler
//
//  Created by lms on 11/29/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include "scanner.h"
#include "error.h"

namespace tinyCompiler {
    Scanner::Scanner(const std::string &srcfileName):fileName_(srcfileName),line_(1),column_(0),currentChar_(0),state_(State::NONE){
        input_.open(fileName_);
        
        if(input_.fail()){
            errorTokenMsg("Try to open " + fileName_ + ",error!");
        }
    }
    
    void Scanner::getNextChar(){
        currentChar_=input_.get();
        
        if(currentChar_=='\n'){
            line_++;
            column_=0;
        }
        else{
            column_++;
        }
    }
    
    char Scanner::peekChar(){
        return  input_.peek();
    }
    
    void Scanner::addToBuffer(char c){
        buffer_.push_back(c);
    }
    
    void Scanner::reduceBuffer(){
        buffer_.pop_back();
    }
    
    void Scanner::makeToken(TokenType tType, TokenValue tValue, const TokenLocation &tLocation,
                   std::string name){
        token_= Token(tType, tValue, tLocation, name);
        buffer_.clear();
        state_ = State::NONE;
    }
    
    void Scanner::makeToken(TokenType tType, TokenValue tValue, const TokenLocation &tLocation,
                            long intValue, std::string name){
        token_= Token(tType, tValue, tLocation, intValue, name);
        buffer_.clear();
        state_ = State::NONE;
    }
    
    void Scanner::pushProcess(){
        do{
            while (std::isspace(currentChar_)) {
                getNextChar();
            }
            
            handleComment();
        }while (std::isspace(currentChar_));
            
    }
    
    void Scanner::handleComment(){
        if(currentChar_=='{'){
            do{
                getNextChar();
                
                //error need to handle, eg:eof
            }while (currentChar_!='}');
        
            if(!input_.eof()){
                getNextChar();
            }
        }
    }
    
    Token Scanner::getNextToken(){
        bool matched = false;
        
        do{
            if(state_!=State::NONE){
                matched=true;
            }
            
            switch (state_) {
                case State::NONE:
                    getNextChar();
                    break;
                
                case State::END_OF_FILE:
                    handleEOFState();
                    break;
                
                case State::IDENTIFIER:
                    handleIdentifierState();
                    break;
                
                case State::NUMBER:
                    handleNumberState();
                    break;
                    
                case State::OPERATION:
                    handleOperationState();
                    break;
                    
                default:
                    errorTokenMsg("Match token state error!");
                    //error need to handle
                    break;
            }
            
            if (state_== State::NONE) {
                pushProcess();
                
                if (input_.eof()) {
                    state_ = State::END_OF_FILE;
                }
                else{
                    if (std::isalpha(currentChar_)) {
                        state_ = State::IDENTIFIER;
                    }
                    else if (std::isdigit(currentChar_)) {
                        state_ = State::NUMBER;
                    }
                    
                    else {
                        state_ = State::OPERATION;
                    }
                }
            }
        }while (!matched);
        
        return token_;
    }
    
    void Scanner::handleEOFState(){
        location_ = getTokenLocation();
        makeToken(TokenType::END_OF_FILE, TokenValue::UNRESERVED, location_, std::string("EOF_OF_FILE"));
        input_.close();
    }
    
    void Scanner::handleIdentifierState(){
        location_ = getTokenLocation();
        
        addToBuffer(currentChar_);
        getNextChar();
        
        while (std::isalnum(currentChar_) || currentChar_ == '_') {
            addToBuffer(currentChar_);
            getNextChar();
        }
        
        //something need to judge, is tiny case sensitive?
        
        auto tokenMeta = dictionary_.lookup(buffer_);
        makeToken(tokenMeta.first, tokenMeta.second, location_, buffer_);
    }
    
    //we can expand number type here ,like 0x...
    //need errorTokenMsg
    void Scanner::handleNumberState(){
        location_ = getTokenLocation();
        
        addToBuffer(currentChar_);
        getNextChar();
        
        while (isdigit(currentChar_)) {
            addToBuffer(currentChar_);
            getNextChar();
        }
        
        makeToken(TokenType::INTERGER, TokenValue::UNRESERVED, location_, std::stol(buffer_,0,10), buffer_);
    }
    
    void Scanner::handleOperationState(){
        location_ = getTokenLocation();
        
        bool matched = false;
        addToBuffer(currentChar_);
        //peek the char ,but the file pointer does not get forward
        addToBuffer(peekChar());
        
        if (dictionary_.haveToken(buffer_)) {
            matched = true;
            getNextChar(); // match two,eat the second
        }
        else{
            reduceBuffer();
        }
        
        auto tokenMeta = dictionary_.lookup(buffer_);
        makeToken(tokenMeta.first, tokenMeta.second, location_, buffer_);
        
        getNextChar();
    }
}
