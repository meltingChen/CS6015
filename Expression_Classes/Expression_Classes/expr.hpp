//
//  expr.hpp
//  Expression_Classes
//
//  Created by 陳肜樺 on 1/22/24.
//

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>

#endif /* expr_hpp */

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
};

class Num : public Expr {};

class Add : public Expr {};

class Mult : public Expr {};
