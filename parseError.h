//
//  parseError.h
//  TinyCompiler
//
//  Created by lms on 12/7/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#ifndef __TinyCompiler__parseError__
#define __TinyCompiler__parseError__

#include "token.h"
#include <string>

namespace tinyCompiler {
    extern void errorParseMsg(Token &token, const std::string &msg);
}


#endif /* defined(__TinyCompiler__parseError__) */
