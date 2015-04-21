//
//  scanner.h
//  TinyCompiler
//
//  Created by lms on 11/29/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#ifndef __TinyCompiler__scanner__
#define __TinyCompiler__scanner__

#include <fstream>
#include "token.h"
#include "dictionary.h"

namespace tinyCompiler {
    class Scanner{
    public:
        Scanner();
        Scanner(const std::string &fileName);
        Token   getToken() const;
        Token   getNextToken();
    private:
        void    getNextChar();
        char    peekChar();
        void    addToBuffer(char c);
        void    reduceBuffer();
        
        void    makeToken(TokenType tType, TokenValue tValue, const TokenLocation &tLocation,
                          std::string name);
        void    makeToken(TokenType tType, TokenValue tValue, const TokenLocation &tLocation,
                          long intValue, std::string name);
        
        //handle state,we don't have string state T_T
        void    handleEOFState();
        void    handleIdentifierState();
        void    handleNumberState();
        void    handleOperationState();
        
        void    pushProcess();
        //handle comment
        void    handleComment();

        TokenLocation getTokenLocation() const;
        
        
        
    private:
        enum class State{
            NONE,
            END_OF_FILE,
            IDENTIFIER,
            NUMBER,
            OPERATION
        };
        
        std::string     fileName_;
        std::fstream    input_;
        char            currentChar_;
        std::string     buffer_;
        
        long            line_;
        long            column_;
        TokenLocation   location_;
        
        Token           token_;
        Dictionary      dictionary_;
        State           state_;
    };
    
    inline Token Scanner::getToken() const{
        return token_;
    }
    
    inline TokenLocation Scanner::getTokenLocation() const{
        return TokenLocation(fileName_, line_, column_);
    }
}

#endif /* defined(__TinyCompiler__scanner__) */
