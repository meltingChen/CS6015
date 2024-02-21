
#ifndef parse_hpp

#define parse_hpp

#include "expr.hpp"
#include <stdio.h>
#include <set>



Expr *parse_expr(std::istream &in);
Expr *parse_num(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr* parse_multicand(std::istream& inn);
Expr* parse_multicand(std::istream& in);
Expr* parse_var(std::istream& in);
// test
Expr* parse_str(std::string s);

#endif
