//
//  parseError.cpp
//  TinyCompiler
//
//  Created by lms on 12/7/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include "parseError.h"

namespace tinyCompiler{
    void errorParseMsg(Token &token, const std::string &msg){
        std::cerr << token.getTokenLocation().getLine() << ":" << token.getTokenLocation().getColumn() << " " << msg << std::endl;
    
    }
}
