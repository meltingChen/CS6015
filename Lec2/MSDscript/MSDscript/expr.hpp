//
//  expr.hpp
//  MSDscript
//
//  Created by 陳肜樺 on 1/22/24.
//

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>
#include <stdexcept>
#include <string>
#include "catch.h"


class Expr {
    
public:
    virtual bool equals(Expr *e) = 0;
//    virtual int evaluate() = 0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e) override;
//    int evaluate() override;
};

class Add : public Expr {
public:
    Expr *lhs; Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr* e) override;
//    int evaluate()override;
};

class Mult : public Expr{
public:
    Expr *lhs; Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;
//    int evaluate()override;
};

class Var : public Expr {
public:
    std::string name;

    Var(std::string name);
    bool equals(Expr *e) override;
//    int evaluate() override;
};

#endif /* expr_hpp */
