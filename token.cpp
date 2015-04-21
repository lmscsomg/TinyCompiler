//
//  token.cpp
//  TinyCompiler
//
//  Created by lms on 11/28/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include "token.h"

namespace tinyCompiler
{
    TokenLocation::TokenLocation(const std::string &fileName, long line, long column)
        :fileName_(fileName),line_(line),column_(column){}
    
    TokenLocation::TokenLocation():fileName_(""), line_(1), column_(0){}
    
    Token::Token(TokenType type, TokenValue value, const TokenLocation &location,
                 std::string name)
        :type_(type),value_(value),location_(location),name_(name){}
    
    Token::Token(TokenType type, TokenValue value, const TokenLocation &location,
                 long intValue, std::string name)
        :type_(type),value_(value),location_(location),intValue_(intValue),name_(name){}
    
    Token::Token() : type_(TokenType::UNKNOWN), value_(TokenValue::UNRESERVED),
        location_(std::string(""), 0, 0), name_(""){}
    
    std::string TokenLocation::toString() const{
        return std::to_string(line_) +":" + std::to_string(column_) + " ";
    }
    
    std::string Token::tokenTypeDescription() const{
        std::string buffer;
        
        switch (type_) {
            case TokenType::INTERGER:
                buffer = "interger:     ";
                break;
            
            case TokenType::IDENTIFIER:
                buffer = "identifier:   ";
                break;
                
            case TokenType::KEYWORD:
                buffer = "keyword:      ";
                break;
                
            case TokenType::OPERATOR:
                buffer = "operator:     ";
                break;
            
            case TokenType::DELIMITER:
                buffer = "delimiter:    ";
                break;
                
            case TokenType::END_OF_FILE:
                buffer = "eof:          ";
                break;
            
            case TokenType::UNKNOWN:
                buffer = "unknown:      ";
                break;
                
            default:
                break;
        }
        return buffer;
    }
    
    void Token::dump(std::ostream &out) const{
        out << location_.toString() << "\t" << tokenTypeDescription() << "\t" << name_ << "\t\t"<<std::endl;
    }
}