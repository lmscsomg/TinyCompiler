//
//  dictionary.h
//  TinyCompiler
//
//  Created by lms on 11/28/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#ifndef __TinyCompiler__Dictionary__
#define __TinyCompiler__Dictionary__

#include <string>
#include <unordered_map>
#include "token.h"

namespace tinyCompiler
{
    class Dictionary{
    public:
        Dictionary();
        std::pair<TokenType, TokenValue> lookup(const std::string &name) const;
        bool haveToken(const std::string &name) const;
    private:
        void addToken(const std::string name, std::pair<TokenType, TokenValue> tokenMeta);

    private:
        std::unordered_map<std::string, std::pair<TokenType, TokenValue>> dictionary_;
    };
}

#endif /* defined(__TinyCompiler__Dictionary__) */
