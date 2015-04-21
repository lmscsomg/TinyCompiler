//
//  token.h
//  TinyCompiler
//
//  Created by lms on 11/28/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#ifndef __TinyCompiler__token__
#define __TinyCompiler__token__

#include <iostream>
#include <utility>

namespace tinyCompiler
{
	enum class TokenType{
		INTERGER,		// only have interger T_T
        IDENTIFIER,     // such as ab
		KEYWORD,		// such as if
		OPERATOR,		// such as + - * /
		DELIMITER,		// such as ;
		END_OF_FILE,	// end of file
        UNKNOWN
	};

	enum class TokenValue{
		// keyword
		IF,
		THEN,
		ELSE,
		END,
		REPEAT,
		UNTIL,
		READ,
		WRITE,

		// symbols
		LEFT_PAREN,		// (
		RIGTH_PAREN,	// )
		PLUS,			// +
		MINUS,			// -
		MULTIPLY,		// *
		DIVIDE,			// /
		ASSIGN,			// :=
		SEMICOLON,		// ;

		// comparation symbols
		EQUAL,			// =
        LESS_THAN,      // <

		UNRESERVED
	};

	class TokenLocation{
	public:
		TokenLocation();
        TokenLocation(const std::string &fileName, long line, long column);
        long getLine() const;
        long getColumn() const;
        std::string toString() const;
        
	private:
		long        line_;
		long        column_;
        std::string fileName_;
	};

	class Token{
	public:
		Token();
		Token(TokenType type, TokenValue value,const TokenLocation &location,
              std::string name);
        Token(TokenType type, TokenValue value, const TokenLocation &location,
              long intValue, std::string name);
        bool operator < (const Token &a) const{
            return this->getTokenName() < a.getTokenName();
        }
		TokenType getTokenType() const;
		TokenValue getTokenValue() const;
		const TokenLocation& getTokenLocation() const;
		std::string getTokenName() const;
        
        std::string tokenTypeDescription() const;
        void dump(std::ostream &out = std::cout) const;
        
	private:
		TokenType       type_;
        TokenValue      value_;
        TokenLocation   location_;
        std::string     name_;
        
        long            intValue_;  //we only have int T_T
	};
    
    inline long TokenLocation::getLine() const{
        return line_;
    }
    
    inline long TokenLocation::getColumn() const{
        return column_;
    }
    
    inline TokenType Token::getTokenType() const{
        return type_;
    }
    
    inline TokenValue Token::getTokenValue() const{
        return value_;
    }
    
    inline std::string Token::getTokenName() const{
        return name_;
    }
    
    inline const TokenLocation& Token::getTokenLocation() const{
        return location_;
    }
}

#endif /* defined(__TinyCompiler__token__) */
