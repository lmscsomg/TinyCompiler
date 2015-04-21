//
//  error.cpp
//  TinyCompiler
//
//  Created by lms on 12/1/14.
//  Copyright (c) 2014 lms. All rights reserved.
//

#include <iostream>
#include "error.h"

namespace tinyCompiler {
    void errorTokenMsg(const std::string &msg){
        std::cerr << "Token Error" << msg << std::endl;
    }
}