//
//  main.cpp
//  test_msdscript
//
//  Created by 陳肜樺 on 2/22/24.
//
#include <string>
#include <iostream>
#include "exec.h"

std::string random_var(){
    std::string s = "";
    for(int i=0;i<rand()%6;i++){
        
        s =(rand()%26) +'a';
    }
    return s;
}

std::string random_mult_and_add(){
    std::string add_or_mult[] = {"*","+"};
    return add_or_mult[rand()%2];
}


std::string random_expr_string() {
    // Num class
    int r = rand();
    if (r % 10 < 2){// 20%
        std::string n = std::to_string(rand());
        return n;
    }
    // Add Class & Mult Class
    else if( r%10 > 2 && r%10 < 6){// 20%

        return random_expr_string() + random_mult_and_add() + random_expr_string();
    }
    
    
    // Let Class
    else if(r%10 <6 && r%10 < 8){// 20%
        
        return "_let" + random_var() + "=" + random_expr_string() + "_in" + random_expr_string();
    }
    
    else
        return random_var(); // 20%
}

int main(int argc, char **argv) {
    // to record the number of errors
    int counter = 0;
  
    const char * const interp_argv[] = { argv[1], "--interp" };
    const char * const print_argv[] = { argv[1], "--print" };
    const char * const pretty_print_argv[] = { argv[1], "--pretty-print" };
    
    for (int i = 0; i < 100; i++) {
        
        std::string in = random_expr_string();
       
        ExecResult interp_result = exec_program(2, interp_argv, in);
        ExecResult print_result = exec_program(2, print_argv, in);
        
        if (argc == 2){
            ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);
            // compare
            if (interp_again_result.out != interp_result.out){
                std::cout << "Trying " << in << "\n";
                std::cout << "result 1: " << interp_again_result.out << "\n";
                std::cout << "result 2: " << interp_result.out << "\n";
                counter++;

            }
        } else if(argc == 3){
            // compare
            const char * const interp2_argv[] = { argv[2], "--interp" };
            const char * const print2_argv[] = { argv[2], "--print" };
            const char * const pretty_print2_argv[] = { argv[2], "--pretty-print" };
            
            ExecResult interp2_result = exec_program(2, interp2_argv, in);
            ExecResult print2_result = exec_program(2, print2_argv, in);
            
            ExecResult pretty_print_result = exec_program(2, pretty_print_argv, in);
            ExecResult pretty_print2_result = exec_program(2, pretty_print2_argv, in);
            // compare
            if (interp_result.out != interp2_result.out){
                std::cout << "My result: " << interp_result.out << "\n";
                std::cout << "Their result: " << interp2_result.out << "\n";
                counter++;

            }
            if (print_result.out != print2_result.out){
                std::cout << "My result: " << print_result.out << "\n";
                std::cout << "Their result: " << print2_result.out << "\n";
                counter++;

            }
            if (pretty_print_result.out != pretty_print2_result.out){
                std::cout << "My result: " << pretty_print_result.out << "\n";
                std::cout << "Their result: " << pretty_print2_result.out << "\n";
                counter++;

            }
        } else {
            throw std::runtime_error("too many aruments");
        }
        
    }
    std::cout<<"It has "<<counter<<"errors"<<std::endl;
    return 0;
    
    
    
//    if(argc>=3){
//        // change the different executable manually
//        const char * const interp1_argv[] = { argv[1], "--interp" };
//        const char * const interp2_argv[] = { argv[2], "--interp" };// compare
//        
//        const char * const print1_argv[] = { argv[1], "--print" };
//        const char * const print2_argv[] = { argv[2], "--print" };// compare
//        
//        const char * const pretty1_print_argv[] = { argv[1], "--pretty_print" };
//        const char * const pretty2_print_argv[] = { argv[2], "--pretty_print" };// compare
//        
//        for (int i = 0; i < 100; i++) {
//            std::string in = random_expr_string();
//            
//            ExecResult interp1_result = exec_program(2, interp1_argv, in);
//            ExecResult interp2_result = exec_program(2, interp2_argv, in);
//            
//            if (interp1_result.out != interp2_result.out) {
//                std::cout << "Trying interp " << i << in << "\n";
//                std::cout << "My result: " << interp1_result.out << "Other's result "<< interp2_result.out<< std::endl;
//            }
//            
//            ExecResult print1_result = exec_program(2, print1_argv, in);
//            ExecResult print2_result = exec_program(2, print2_argv, in);
//    
//    
//            if (print1_result.out != print2_result.out){
//                std::cout << "Trying print " << i << in << "\n";
//                std::cout << "My result: " << print1_result.out << "Other's result "<< print2_result.out<< std::endl;
//            } ;
//    
//            //------------------------------------------------------------------------------------------
//            ExecResult pretty1_print_result = exec_program(2, pretty1_print_argv, in);
//            ExecResult pretty_print2_result = exec_program(2, pretty1_print_argv, in);
//    
//            
//            if (pretty1_print_result.out != pretty_print2_result.out) {
//                std::cout << "Trying pretty_print " << i << in << "\n";
//                std::cout << "My result: " << pretty1_print_result.out << "Other's result "<< pretty_print2_result.out<< std::endl;
//            }
//        }}
//    else if (argc==2){
//        for (int i = 0; i < 100; i++) {
//            
//            const char * const interp1_argv[] = { argv[1], "--interp" };
//            const char * const interp2_argv[] = { argv[1], "--interp" };
//            
//            const char * const print_argv[] = { argv[1], "--print" };
//            const char * const pretty_print_argv[] = { argv[1], "--pretty_print" };
//            
//            
//            std::string in = random_expr_string();
//            std::cout << "Trying: "<< in << "\n";
//            
//            ExecResult interp_result = exec_program(2, interp1_argv, in);
//            ExecResult print_result = exec_program(2, print_argv, in);
//            ExecResult pretty_print_result = exec_program(2, print_argv, in);
//            
//            
//            if (pretty_print_result.out != interp_result.out)
//                throw std::runtime_error("Different result for printed");
//             
//        }
//        
//    }
//    return 0;
}
        
        
        //------------------------------------------------------------------------------------------
//        ExecResult print1_result = exec_program(2, print1_argv, in);
//        ExecResult print2_result = exec_program(2, print2_argv, in);
//        
//        
//        if (print1_result.out != print2_result.out) ;
//        
//        //------------------------------------------------------------------------------------------
//        ExecResult pretty1_print_result = exec_program(2, pretty1_print_argv, in);
//        ExecResult pretty2_print2_result = exec_program(2, pretty1_print_argv, in);
//        
        
//        if (pretty1_print_result.out != pretty2_print2_result.out) throw std::runtime_error("different results");
//        
        

