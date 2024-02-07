//  expr.cpp
//  MSDscript
//
//  Created by 陳肜樺 on 1/22/24.
//

#include "expr.hpp"


std::string Expr::to_string() {
    // Convert "" to a stringstream object
    std::stringstream st("");
    this->print(st);
    return st.str();
}

std::string Expr::to_pretty_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}

void Expr::pretty_print(std::ostream& ot) {
    pretty_print_at(ot, prec_none);
    
}

Num::Num(int val)  {
    this->val = val;
}

bool Num::equals(Expr* e){
    Num *n = dynamic_cast<Num*>(e);
    
    if(n==NULL){
        return false;
    }
    return this->val == n->val;
}

int Num::interp(){
    
    return this->val;
}

bool Num::has_variable(){
    return false;
}


Expr* Num::subst(std::string s, Expr* e){
    
    return this;
}

void Num::print(std::ostream& ot){
    
    ot<<std::to_string(val);
}

void Num::pretty_print_at(std::ostream& ot,precedence_t prec ){
    this->print(ot);
}



Add::Add(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr* e){
    Add *n = dynamic_cast<Add*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return n->rhs->equals( this->rhs) && n->lhs->equals(this->lhs);
}

int Add::interp(){
//    Num *lhs_num = dynamic_cast<Num*>(this->lhs);
//    Num * rhs_num = dynamic_cast<Num*>(this->rhs);
    
    return lhs -> interp()  + rhs -> interp();
    
}

bool Add::has_variable(){
    
    return ((this->lhs->has_variable()==true) || (this->rhs->has_variable()==true));
}

Expr* Add::subst(std::string s, Expr* e){
    //think recursively
    
    return new Add(this->lhs->subst(s, e), this->rhs->subst(s, e)) ;
}

void Add::print(std::ostream& ot){
    
    ot << "(";
    lhs->print(ot);
    ot << "+";
    rhs->print(ot);
    ot << ")";
    
}


void Add::pretty_print_at(std::ostream& ot,precedence_t prec ) {
    bool do_print = prec_add <= prec;
    if(do_print){
        ot<<"(";
    }
    lhs->pretty_print_at(ot, prec_add);
    ot<<" + ";
    // operators associate to the right
    rhs -> pretty_print_at(ot, prec_none);
    if(do_print){
        ot<<")";
    }
//    std::string result;
//    if (prec >= prec_add) {
//        result += "(";
//    }
//    result += lhs-> pretty_print(prec_add) + " + " + rhs-> pretty_print(prec_add);
//    if (prec >= prec_add) {
//        result += ")";
//    }
    
}
   



Mult::Mult(Expr* lhs, Expr* rhs){
    
    this->lhs = lhs;
    this->rhs = rhs;
    
}

bool Mult::equals(Expr *e){
    Mult *n = dynamic_cast<Mult*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return n->rhs->equals( this->rhs) && n->lhs->equals(this->lhs);
}

int Mult::interp(){
   
//    Num *lhs_num = dynamic_cast<Num*>(this->lhs);
//    Num * rhs_num = dynamic_cast<Num*>(this->rhs);
    return this-> lhs -> interp()  * this->rhs->interp();
    
    
}

bool Mult::has_variable(){
   
    return ((this->lhs->has_variable()==true) || (this->rhs->has_variable()==true));
}

Expr* Mult::subst(std::string s, Expr* e){
    
    return new Mult(this->lhs->subst(s, e), this->rhs->subst(s, e));
}

void Mult::print(std::ostream& ot) {
    ot << "(";
    lhs->print(ot);
    ot << "*";
    rhs->print(ot);
    ot << ")";
}


void Mult::pretty_print_at(std::ostream& ot,precedence_t prec ) {
    
    bool do_print = prec_mult <= prec;
    if(do_print){
        ot<<"(";
    }
    lhs->pretty_print_at(ot, prec_mult);
    ot<<" * ";
    // operators associate to the right
    rhs->pretty_print_at(ot, prec_add);
    if(do_print){
        ot<<")";
    }
    

}




Var::Var(std::string name) {
    this -> name = name;
}

bool Var::equals(Expr *e) {
    Var *n = dynamic_cast<Var*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return this -> name == n -> name;
}

int Var::interp() {
    throw std::runtime_error("no value for variable");
}

bool Var::has_variable(){
    return true;
}

Expr* Var::subst(std::string s, Expr* e){
    if(s == (this->name)){
        return e;
    }
    return this;
}

void Var::print(std::ostream& output) {
    output << this->name;
}

void Var::pretty_print_at(std::ostream& ot,precedence_t prec){
    this->print(ot);
}





TEST_CASE("Tests"){
    SECTION("HW2"){
        //Check Num class
        CHECK( (new Num(1))->equals(new Var("x")) == false );
        CHECK( (new Num(5))->equals(new Num(100000000)) == false );
        
        //Check Var class
        CHECK( (new Var(""))->equals(new Var("")) == true );
        CHECK( (new Num(0))->equals(new Var("x")) == false );
        CHECK( (new Var("x"))->equals(new Var("x")) == true );
        CHECK( (new Var("x"))->equals(new Var("y")) == false );
        
        //Check Add class
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
        CHECK( (new Add(new Num(0),new Num(0)))->equals(new Add(new Num(0),new Num(0)))==true );
        //        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Num(5))==true );
        
        //Check Mult class
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(2),new Num(3)))==true );
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(3),new Num(2)))==false );
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(3)))==false );
        CHECK( (new Mult(new Num(0),new Num(3)))->equals(new Mult(new Num(3),new Num(0)))==false );
    }
    SECTION("interp"){
        CHECK( (new Num(0))->interp()==0 );
        CHECK( (new Num(-5))->interp()==-5 );
        CHECK( (new Num(10))->interp()==10 );
        CHECK( (new Num(100))->interp()==100 );
        CHECK_THROWS_WITH( (new Var("x"))->interp(), "no value for variable");
        CHECK( (new Mult(new Num(0), new Num(0)))->interp()==0 );
        CHECK( (new Mult(new Num(10), new Num(0)))->interp()==0 );
        CHECK( (new Mult(new Num(3), new Num(2)))->interp()==6 );
        CHECK( (new Mult(new Num(10), new Num(10)))->interp()==100 );
        CHECK( (new Add(new Add(new Num(0), new Num(0)),new Add(new Num(0),new Num(0)))) ->interp()==0);
        CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20)))) ->interp()==65);
        CHECK( (new Add(new Add(new Num(-10), new Num(15)),new Add(new Num(-20),new Num(20)))) ->interp()==5);
        CHECK( (new Add(new Add(new Num(-15), new Num(15)),new Add(new Num(-20),new Num(20)))) ->interp()==0);
        CHECK( (new Add(new Add(new Num(-20), new Num(15)),new Add(new Num(-20),new Num(20)))) ->interp()==-5);
       
    }
    SECTION("has_variable"){
        CHECK( (new Var(""))->has_variable() == true );
        CHECK( (new Var("x"))->has_variable() == true );
        CHECK( (new Num(0))->has_variable() == false );
        CHECK( (new Mult(new Num(2), new Num(1)))->has_variable() == false );
        CHECK( (new Mult(new Var("x"), new Num(1)))->has_variable() == true );
        CHECK( (new Add(new Var("x"), new Num(1)))->has_variable() == true );
        CHECK( (new Add(new Var("x"), new Num(1)))->has_variable() == true );
        
    }
    SECTION("subst"){
    
        CHECK( (new Add(new Var("x"), new Num(7)))
               ->subst("x", new Var("y"))
               ->equals(new Add(new Var("y"), new Num(7))) );
        CHECK( (new Add(new Var("x"), new Num(7)))
               ->subst("y", new Var("y"))
               ->equals(new Add(new Var("x"), new Num(7))) );
        CHECK( (new Var("x"))
               ->subst("x", new Add(new Var("y"),new Num(7)))
               ->equals(new Add(new Var("y"),new Num(7))) );
        CHECK( (new Var("y"))
               ->subst("x", new Add(new Var("y"),new Num(7)))
               ->equals(new Var("y") ));
        CHECK( (new Num(1))
               ->subst("x", new Add(new Var("y"),new Num(7)))
               ->equals(new Num(1) ));
        CHECK( (new Mult(new Var("x"), new Num(7)))
               ->subst("x", new Var("y"))
               ->equals(new Mult(new Var("y"), new Num(7))) );
        CHECK( (new Mult(new Var("x"), new Num(7)))
               ->subst("x", new Var("y"))
               ->equals(new Mult(new Var("y"), new Num(7))) );
        
    }
    SECTION("print"){
        CHECK( (new Num(10))->to_string() == "10" );
        CHECK( (new Num(0))->to_string() == "0" );
        CHECK( (new Var("x"))->to_string() == "x" );
        CHECK( (new Var(""))->to_string() == "" );
        CHECK( (new Add(new Num(2), new Num(3)))->to_string() == "(2+3)" );
        CHECK( (new Add(new Num(0), new Num(3)))->to_string() == "(0+3)" );
        CHECK( (new Mult(new Var("x"), new Num(5)))->to_string() == "(x*5)" );
        CHECK( (new Add(new Mult(new Var("x"), new Num(5)),new Num(7)))->to_string() == "((x*5)+7)" );
        CHECK( (new Mult(new Mult(new Var("x"), new Num(5)),new Num(7)))->to_string() == "((x*5)*7)" );
        CHECK( (new Mult(new Mult(new Var("x"), new Num(5)),new Add(new Num(6),new Num(8))))->to_string() == "((x*5)*(6+8))" );
    
    }
    SECTION("pretty_print"){
        CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
        CHECK ( (new Add(new Num(1), new Mult(new Num(2), new Num(3))))->to_pretty_string() ==  "1 + 2 * 3" );
        CHECK ( (new Add(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 + 2 + 3" );
        CHECK ( (new Mult (new Num(2), new Mult (new Num(3), new Num(4))))->to_pretty_string() == "2 * 3 * 4" );
        CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() ==  "(8 * 1) * y" );
        CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
        CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );
        CHECK ( (new Mult(new Num(7), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "7 * (9 + 2)" );
        CHECK ( (new Add(new Num(7), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "7 + 9 + 2" );

    }
};
