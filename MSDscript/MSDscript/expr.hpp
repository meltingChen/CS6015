/**
* \classes expr
*/

#ifndef expr_hpp
#define expr_hpp

#include "catch.h"
#include <stdio.h>
#include <stdexcept>
#include <ios>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

// Magic numbers
typedef enum {
  prec_none, // = 0
  prec_add,  // = 1
  prec_mult, // = 2
} precedence_t;

class Expr {
    
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() =0;
    virtual Expr* subst(std::string s, Expr* e)=0;
    virtual void print(std::ostream& ot)=0;
    std::string to_string();
    void pretty_print(std::ostream& ot);
    std::string to_pretty_string();
    virtual void pretty_print_at(std::ostream& ot,precedence_t prec ,std::streampos& newLinePos,bool print_outer)=0;
};

class Let: public Expr{
public:
    std::string name;
    Expr* bindExpr;
    Expr* rhs;
    Let(std::string name,Expr* blindExpr, Expr* rhs);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
    void print(std::ostream& ot)override;
    void pretty_print_at(std::ostream& ot,precedence_t prec, std::streampos& newLinePos ,bool print_outer)override;
};

class Num : public Expr {
public:
    int val;///< the value of a Num object
    Num(int val);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
    void print(std::ostream& ot)override;
    void pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos,bool print_outer)override;
};

class Add : public Expr {
public:
    Expr *lhs; ///< an Expr object on the left hand side
    Expr *rhs; ///< an Expr object on the right hand side
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr* e) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
    void print(std::ostream& ot)override;
    void pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos,bool print_outer)override;
    
};

class Mult : public Expr{
public:
    Expr *lhs;///< an Expr object on the left hand side
    Expr *rhs;///< an Expr object on the right hand side
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) override;
    int interp()override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
    void print(std::ostream& ot)override;
    void pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos ,bool print_outer)override;
    
};

class Var : public Expr {
public:
    std::string name;///< the name of an Var object

    Var(std::string name);
    bool equals(Expr *e) override;
    int interp() override;
    bool has_variable()override;
    Expr* subst(std::string s, Expr* e)override;
    void print(std::ostream& ot)override;
    void pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos ,bool print_outer)override;
};

#endif /* expr_hpp */
