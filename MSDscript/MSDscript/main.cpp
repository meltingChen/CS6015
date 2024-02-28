/**
* \mainpage MSDScript
* \author Tina Chen
* \date 07-02-2023
*/

#include <iostream>
#include <string>
#include "cmdline.hpp"
#include "parse.hpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    run_mode_t mode = use_arguments(argc, argv);
    
    if(mode != do_nothing){
        Expr* e = parse_expr(std::cin);
        switch (mode) {
            case do_nothing:
                break;
            case do_interp:
                std::cout << e->interp()<<"\n";
                break;
            case do_print:
                std::cout << e->to_string()<<"\n";
                break;
            case do_pretty_print:
                std::cout << e->to_pretty_string()<<"\n";
                break;
                
        }
    }
    
    
//    std::cout << (new Let("x", new Num(5), new Let("y", new Num(6), new Add(new Var("x"), new Num(1))))) ->to_pretty_string();
//    std::cout<< parse_str("-")->to_string()<<std::endl;
//    std::cout<<parse_str(" -   5  ")->to_string()<<std::endl;
    
    return 0;
}
