//
//  expr.cpp
//  MSDscript
//
//  Created by 陳肜樺 on 1/22/24.
//

#include "expr.hpp"

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

//int Num::evaluate(){
//
//    return this->val;
//}

Add::Add(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
};

bool Add::equals(Expr* e){
    Add *n = dynamic_cast<Add*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return n->rhs->equals( this->rhs) && n->lhs->equals(this->lhs);
}

//int Add::evaluate(){
//
//    return dynamic_cast<Num*>(this->lhs)->val + dynamic_cast<Num*>(this->rhs)->val;
//}

Mult::Mult(Expr *lhs, Expr *rhs){
    
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
//int Mult::evaluate(){
//    return dynamic_cast<Num*>(this->lhs)->val * dynamic_cast<Num*>(this->rhs)->val;
//}

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

//int Var::evaluate() {
//    return NULL;
//}



TEST_CASE("Tests"){
    SECTION("HW2"){
        //Check Num class
        CHECK( (new Num(1))->equals(new Var("x")) == false );
        CHECK( (new Num(5))->equals(new Num(100000000)) == false );
        
        //Check Var class
        CHECK( (new Var(""))->equals(new Var("")) == true );
        CHECK( (new Num(0))->equals(new Var("x")) == true );
        CHECK( (new Var("x"))->equals(new Var("x")) == true );
        CHECK( (new Var("x"))->equals(new Var("y")) == false );
        
        //Check Add class
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
        CHECK( (new Add(new Num(0),new Num(0)))->equals(new Add(new Num(0),new Num(0)))==false );
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Num(5))==true );
        
        //Check Mult class
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(2),new Num(3)))==true );
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(3),new Num(2)))==false );
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(3)))==true );
        CHECK( (new Mult(new Num(0),new Num(3)))->equals(new Mult(new Num(3),new Num(0)))==false );
    }
};
