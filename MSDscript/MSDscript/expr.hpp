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

#include <cstring>
#include <string>

#include "catch.h"
#include <stdexcept>


class Expr {
    
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() =0;
    virtual Expr* subst(std::string s, Expr* e)=0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
};

class Add : public Expr {
public:
    Expr *lhs; Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr* e) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
};

class Mult : public Expr{
public:
    Expr *lhs; Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
};

class Var : public Expr {
public:
    std::string name;

    Var(std::string name);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
};

#endif /* expr_hpp */
