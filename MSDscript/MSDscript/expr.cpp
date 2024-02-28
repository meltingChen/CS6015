//  expr.cpp
//  MSDscript
//
//  Created by on 1/22/24.
//

#include "expr.hpp"

/**
 * \brief Print out the result of print() function
 * \return string
 */
std::string Expr::to_string() {
    // Convert "" to a stringstream object
    std::stringstream st("");
    this->print(st);
    return st.str();
}

/**
 * \brief Print out the result of pretty_print() function
 * \return string
 */
std::string Expr::to_pretty_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}

/**
 * \brief Make the format look better
 */
void Expr::pretty_print(std::ostream& ot) {
    std::streampos pos = ot.tellp();
    pretty_print_at(ot, prec_none ,pos,false);
}


Let::Let(std::string name,Expr* blindExpr, Expr* rhs){
    this -> name = name;
    this ->bindExpr = blindExpr;
    this -> rhs = rhs;
}

bool Let::equals(Expr *e) {
    Let *n = dynamic_cast<Let*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return (n->name)==(this->name) && n->bindExpr->equals( this->bindExpr) && n->rhs->equals(this->rhs);
    
}
int Let::interp() {
    int bind_n = this->bindExpr->interp();
    Num* bind_n_Expr = new Num(bind_n);
    
    return this->rhs->subst(name, bind_n_Expr)->interp();
}

bool Let::has_variable(){
    return (this->rhs->has_variable()==true);
}

Expr* Let::subst(std::string s, Expr* e){
   
    if( s == this ->name){
     return new Let(s,bindExpr,rhs);
    }
    
    return new Let(name,bindExpr,this-> rhs->subst(s, e)) ;
}
void Let::print(std::ostream& ot){
    ot << "(_let "+name+"=";
    bindExpr->print(ot);
    ot << " _in ";
    rhs->print(ot);
    ot << ")";
    
}
void Let::pretty_print_at(std::ostream& ot,precedence_t prec, std::streampos& newLinePos, bool add_let_paren)
{
    
    if(add_let_paren){
        ot << "(";
    }
    std::streampos curr = ot.tellp() - newLinePos;
    ot<<"_let "+name+" = ";
    bindExpr->pretty_print_at(ot, prec_none, newLinePos, false);
    ot<<"\n";
    std::streampos before_in = ot.tellp();
    ot<<std::string(curr,' ');
    
    ot<<"_in ";
    
    rhs -> pretty_print_at(ot,prec_none,before_in,false);

    if(add_let_paren){
        ot<<")";
    }
}





/**
 * \brief Constuctor of Num object
 * \param val the value of a Num object
 */
Num::Num(int val)  {
    this->val = val;
}

/**
 * \brief Compare whether two expression are equal
 * \param e an expressionto be compared
 * \return boolean
 */
bool Num::equals(Expr* e){
    Num *n = dynamic_cast<Num*>(e);
    
    if(n==NULL){
        return false;
    }
    return this->val == n->val;
}

/**
 * \brief Interpret the value
 * \return int
 */
int Num::interp(){
    
    return this->val;
}

/**
 * \brief To check whether there are any variables in expressions
 * \return boolean
 */
bool Num::has_variable(){
    return false;
}


/**
 * \brief If the first argument exists, it will be substitued with the second argument
 * \param s the value to be substitued
 * \param e the replacement
 * \return Expression itself
 */
Expr* Num::subst(std::string s, Expr* e){
    
    return this;
}

/**
 * \brief To print out the expression
 * \param ot the outputstream to be written
 */
void Num::print(std::ostream& ot){
    
    ot<<std::to_string(val);
}

/**
 * \brief Helper funtion for pretty_print to decide where to add parentheses
 * \param ot the outputstream to be written
 * \param prec the order of importance
 */
void Num::pretty_print_at(std::ostream& ot,precedence_t prec, std::streampos& newLinePrevPos,bool add_let_paren ){
    this->print(ot);
}


/**
 * \brief Constuctor of Add object
 * \param lhs an Expr object on the right hand side
 * \param rhs an Expr object on the left hand side
 */
Add::Add(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Compare whether two expression are equal
 * \param e an expressionto be compared
 * \return boolean
 */
bool Add::equals(Expr* e){
    Add *n = dynamic_cast<Add*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return n->rhs->equals( this->rhs) && n->lhs->equals(this->lhs);
}

/**
 * \brief Interpret the value
 * \return int
 */
int Add::interp(){
   
    return lhs -> interp()  + rhs -> interp();
    
}

/**
 * \brief To check whether there are any variables in expressions
 * \return boolean
 */
bool Add::has_variable(){
    
    return ((this->lhs->has_variable()==true) || (this->rhs->has_variable()==true));
}

/**
 * \brief If the first argument exists, it will be substitued with the second argument
 * \param s the value to be substitued
 * \param e the replacement
 * \return Expression itself
 */
Expr* Add::subst(std::string s, Expr* e){
    //think recursively
    
    return new Add(this->lhs->subst(s, e), this->rhs->subst(s, e)) ;
}

/**
 * \brief To print out the expression
 * \param ot the outputstream to be written
 */
void Add::print(std::ostream& ot){
    
    ot << "(";
    lhs->print(ot);
    ot << "+";
    rhs->print(ot);
    ot << ")";
    
}

/**
 * \brief Helper funtion for pretty_print to decide where to add parentheses
 * \param ot the outputstream to be written
 * \param prec the order of importance
 */
void Add::pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos,bool add_let_paren ) {
    bool do_print = prec_add <= prec;

    if(do_print){
        ot<<"(";
    }
    lhs->pretty_print_at(ot, prec_add,newLinePos,true);
    ot<<" + ";
    // operators associate to the right
    rhs -> pretty_print_at(ot, prec_none, newLinePos, add_let_paren);
    if(do_print){
        ot<<")";
    }
    
}



/**
 * \brief Constuctor of Mult object
 * \param lhs an Expr object on the right hand side
 * \param rhs an Expr object on the left hand side
 */
Mult::Mult(Expr* lhs, Expr* rhs){
    
    this->lhs = lhs;
    this->rhs = rhs;
    
}

/**
 * \brief Compare whether two expression are equal
 * \param e an expressionto be compared
 * \return boolean
 */
bool Mult::equals(Expr *e){
    Mult *n = dynamic_cast<Mult*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return n->rhs->equals( this->rhs) && n->lhs->equals(this->lhs);
}

/**
 * \brief Interpret the value
 * \return int
 */
int Mult::interp(){
    
    
    return this-> lhs -> interp()  * this->rhs->interp();
    
    
}

/**
 * \brief To check whether there are any variables in expressions
 * \return boolean
 */
bool Mult::has_variable(){
    
    return ((this->lhs->has_variable()==true) || (this->rhs->has_variable()==true));
}

/**
 * \brief If the first argument exists, it will be substitued with the second argument
 * \param s the value to be substitued
 * \param e the replacement
 * \return Expression itself
 */
Expr* Mult::subst(std::string s, Expr* e){
    
    return new Mult(this->lhs->subst(s, e), this->rhs->subst(s, e));
}

/**
 * \brief To print out the expression
 * \param ot the outputstream to be written
 */
void Mult::print(std::ostream& ot) {
    ot << "(";
    lhs->print(ot);
    ot << "*";
    rhs->print(ot);
    ot << ")";
}

/**
 * \brief Helper funtion for pretty_print to decide where to add parentheses
 * \param ot the outputstream to be written
 * \param prec the order of importance
 */
void Mult::pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos,bool add_let_paren ) {
    
    bool do_print = prec_mult <= prec;
    bool let_print = add_let_paren;
    if(do_print){
        ot<<"(";
        let_print = false;
    }
    lhs->pretty_print_at(ot, prec_mult,newLinePos,true);
    ot<<" * ";
    // operators associate to the right
    rhs->pretty_print_at(ot, prec_add,newLinePos, let_print);
    if(do_print){
        ot<<")";
    }
    
    
}

/**
 * \brief Constuctor of Var object
 * \param name the name of the Var object
 */
Var::Var(std::string name) {
    this -> name = name;
}

/**
 * \brief Compare whether two expression are equal
 * \param e an expressionto be compared
 * \return boolean
 */
bool Var::equals(Expr *e) {
    Var *n = dynamic_cast<Var*>(e);
    
    if(n==NULL){
        return false;
    }
    
    return this -> name == n -> name;
}

/**
 * \brief Interpret the value
 * \return int
 */
int Var::interp() {
    throw std::runtime_error("no value for variable");
}

/**
 * \brief To check whether there are any variables in expressions
 * \return boolean
 */
bool Var::has_variable(){
    return true;
}

/**
 * \brief If the first argument exists, it will be substitued with the second argument
 * \param s the value to be substitued
 * \param e the replacement
 * \return Expression itself
 */
Expr* Var::subst(std::string s, Expr* e){
    if(s == (this->name)){
        return e;
    }
    return this;
}

/**
 * \brief To print out the expression
 * \param ot the outputstream to be written
 */
void Var::print(std::ostream& ot) {
    ot << this->name;
}

/**
 * \brief Helper funtion for pretty_print to decide where to add parentheses
 * \param ot the outputstream to be written
 * \param prec the order of importance
 */
void Var::pretty_print_at(std::ostream& ot,precedence_t prec,std::streampos& newLinePos,bool add_let_paren){
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
    SECTION("Let"){
        CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->equals(new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))==true);
        CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->equals(new Num(7))==false);
        CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->has_variable()==true);
        // print
        CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->to_string()=="(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((new Let("x", new Num(5), new Let("x", new Num(6), new Add(new Var("x"), new Num(1)))))->to_string()=="(_let x=5 _in (_let x=6 _in (x+1)))");
        // interp()
        CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->interp()==10);
        CHECK((new Let("x", new Num(5), new Let("x", new Num(6), new Add(new Var("x"), new Num(1)))))->interp()==7);
        CHECK((new Let("x", new Num(5), new Add(new Var("x"), new Mult(new Num(1), new Num(2)))))->interp()==7);
        
        
        
        // subst
        CHECK((new Let("x", new Num(5), new Let("y", new Num(6), new Add(new Var("x"), new Num(1)))))
              ->interp()==6
              );
        CHECK((new Let("x", new Num(5), new Let("x", new Num(6), new Add(new Var("x"), new Num(1)))))
              ->interp()==7
              );
        CHECK((new Let("x", new Add(new Num(5), new Num(2)), new Add(new Var("x"), new Num(1) )))->interp()==8);
        CHECK((new Let("x", new Num(5), new Add(new Var("x"), new Num(3))))->to_pretty_string() ==  "_let x = 5\n_in x + 3");
        //        /Let nested as right argument of parenthesized multiplication expression
        SECTION("test pretty print"){
            //Let nested as right argument of parenthesized multiplication expression
            CHECK ( (new Mult(new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") , new Num(1)) )), new Num(3)))->to_pretty_string() == "(2 * _let x = 5\n"
                   "     _in x + 1) * 3");
            //Let nested to the left in add expression which is nested to the right within a multiplication expression
            CHECK((new Mult(new Num(5), new Add(new Let("x", new Num(5), new Var("x")), new Num(1))))->to_pretty_string() == "5 * ((_let x = 5\n"
                  "      _in x) + 1)");
            //Let in lhs of add
            CHECK ( (new Add(new Let("x", new Num(2), new Add(new Var("x"), new Num(9))), new Num(4)))->to_pretty_string() == "(_let x = 2\n"
                   " _in x + 9) + 4");
            //Let in lhs of multiplication expression
            CHECK((new Mult(new Let("x", new Num(5), new Add(new Var("x"), new Num(8))), new Num(3)))->to_pretty_string() == "(_let x = 5\n"
                  " _in x + 8) * 3");
            //Let nest as right argument of un-parenthesized multiplication expression
            CHECK((new Add (new Mult(new Num(4), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))), new Num(9)))->to_pretty_string() == "4 * (_let x = 5\n"
                  "     _in x + 1) + 9");
            
            
            //Let nested in lhs of Add expression nested within body of let expression
            CHECK((new Let("x", new Num(5), new Add(new Let("y" , new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                  ->to_pretty_string() == "_let x = 5\n"
                  "_in (_let y = 3\n"
                  "     _in y + 2) + x");
            
            
            
            CHECK( ( new Let( "x", new Num(5),
                             new Add( new Let( "y", new Num(3),
                                              new Add( new Var("y"), new Let("z",new Num(6),
                                                                             new Add(new Var("a"), new Num(8))) ) ), new Var("x") ) ) )
                  ->to_pretty_string()== "_let x = 5\n"
                  "_in (_let y = 3\n"
                  "     _in y + _let z = 6\n"
                  "             _in a + 8) + x" );
            
            CHECK ((new Add(new Let("x", new Num(3), new Let("y", new Num(3), new Add(new Var("y"), new Num(2))) ), new Var("x")))->to_pretty_string() == "(_let x = 3\n"
                " _in _let y = 3\n"
                "     _in y + 2) + x");
            
            
            
            //this code block just allows for the printing of some statements to the terminal. Also used for debugging.
            
            //            std::cout << (new Add(new _let("x", new Num(3), new _let("y", new Num(3), new Add(new Var("y"), new Num(2))) ), new Var("x")))->to_pretty_string();
            //        std::cout << std::endl;
            //        std::cout << ( new _let( "x", new Num(5),new Add( new _let( "y", new Num(3),new Add( new Var("y"), new _let("z",new Num(6),new Add(new Var("a"), new Num(8))) ) ), new Var("x") ) ) )->to_pretty_string();
            //
            
        }
        
        
        
        SECTION("nabil"){
            CHECK( (new Let("x", new Num(5), new Var("x")))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "_let x = 5\n" +
                      "_in x") );
            CHECK( (new Let("x", new Num(5),
                            new Add(new Let("y", new Num(3),
                                            new Add(new Var("y"), new Num(2))),
                                    new Var("x"))))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "_let x = 5\n" +
                      "_in (_let y = 3\n" +
                      "     _in y + 2) + x") );
            CHECK( (new Let("x", new Num(5),
                            new Add(new Var("x"),
                                    new Let("y", new Num(3),
                                            new Add(new Var("y"), new Num(2))))))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "_let x = 5\n" +
                      "_in x + _let y = 3\n" +
                      "        _in y + 2") );
            CHECK( (new Let("x", new Num(5),
                            new Mult(new Let("y", new Num(3),
                                             new Mult(new Var("y"), new Num(2))),
                                     new Var("x"))))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "_let x = 5\n" +
                      "_in (_let y = 3\n" +
                      "     _in y * 2) * x") );
            CHECK( (new Let("x", new Num(5),
                            new Mult(new Var("x"),
                                     new Let("y", new Num(3),
                                             new Mult(new Var("y"), new Num(2))))))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "_let x = 5\n" +
                      "_in x * _let y = 3\n" +
                      "        _in y * 2") );
            CHECK( (new Let("x", new Let("z", new Num(8),
                                         new Var("z")),
                            new Let("y", new Num(3),
                                    new Add(new Var("y"), new Var("x")))))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "_let x = _let z = 8\n" +
                      "         _in z\n" +
                      "_in _let y = 3\n" +
                      "    _in y + x") );
            CHECK( (new Add(new Mult(new Num(5),
                                     new Let("x", new Num(5), new Var("x"))),
                            new Num(1)))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "5 * (_let x = 5\n" +
                      "     _in x) + 1") );
            CHECK( (new Mult(new Mult(new Num(5),
                                      new Let("x", new Num(5), new Var("x"))),
                             new Num(3)))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "(5 * _let x = 5\n" +
                      "     _in x) * 3") );
            CHECK( (new Add(new Num(1),
                            new Add(new Let("x", new Num(5), new Var("x")),
                                    new Num(2))))
                  ->to_pretty_string()
                  == ((std::string)"" +
                      "1 + (_let x = 5\n" +
                      "     _in x) + 2") );
            CHECK ((new Add(new Let("x", new Num(3), new Let("y", new Num(3), new Add(new Var("y"), new Num(2))) ), new Var("x")))->to_pretty_string() ==
                   "(_let x = 3\n"
                   " _in _let y = 3\n"
                   "     _in y + 2) + x" );
            CHECK((new Let("x", new Num(5), new Add(new Let("y" , new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                  ->to_pretty_string() ==
                  "_let x = 5\n"
                  "_in (_let y = 3\n"
                  "     _in y + 2) + x");
            CHECK( ( new Let( "x", new Num(5), new Add( new Let( "y", new Num(3), new Add( new Var("y"), new Let("z",new Num(6), new Add(new Var("a"), new Num(8))) ) ), new Var("x") ) ) )
                  ->to_pretty_string()==
                  "_let x = 5\n"
                  "_in (_let y = 3\n"
                  "     _in y + _let z = 6\n"
                  "             _in a + 8) + x" );
        }
    }
};
