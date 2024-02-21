//
//  cmdline.hpp
//  MSDscript
//
//  Created by on 1/14/24.
//

#ifndef cmdline_hpp
#define cmdline_hpp


#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <stdexcept>
#include "catch.h"

typedef enum {
    
    do_nothing,
    do_interp,
    do_print,
    do_pretty_print
    
} run_mode_t;



run_mode_t use_arguments(int argc,const char * argv[]);


#endif /* cmdline_hpp */
