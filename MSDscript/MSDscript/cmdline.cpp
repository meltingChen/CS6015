//
//  cmdline.cpp
//  MSDscript
//
//  Created by on 1/14/24.
//

#define CATCH_CONFIG_RUNNER
#include "cmdline.hpp"
#include <cstring>
#include <cstdlib>


using namespace std;
static void check_mode_already(run_mode_t mode, std::string flag);

/**
* \brief Define the argument that can be use to in MSDScript progam
* \param argc the number of input
* \param argv input
*/
run_mode_t use_arguments(int argc,const char * argv[]){
    bool testTracker = false;// bool
    run_mode_t mode = do_nothing;
    
    for(int i =1 ;i<argc;i++){
        
        if(strcmp(argv[i],"--help")==0){
            cout<<"Available flags:"<<endl;
            cout<<"--test :run tests"<<endl;
            cout<<"--help : this help"<<endl;
            exit(0);
        }
        // --test : run tests and exit with a 0 status if all pass, a non-zero status if there are any failures
        else if(strcmp(argv[i],"--test")==0){
            if(testTracker!=true){
                testTracker = true;
                if( Catch::Session().run(1, argv)!=0){
                    std::cerr << "Tests failed!" << std::endl;
                    exit(1);
                }
                else{
                    std::cout << "All tests passed!" << std::endl;
                    testTracker = true;
                    exit(0);
                }
                
            }
            else{
                cerr<<"Duplicate --test"<<endl;
                exit(1);
            }
        }
        //--interp : accept a single expression on standard input, parse it, interp it, print the result to standard output, and print a newline, exiting with a 0 status
        else if(strcmp(argv[i],"--interp")==0){
            check_mode_already(mode,argv[i]);
            mode = do_interp;
//            if (i + 1 < argc) {
//                return do_interp;
//                
//            } else {
//                throw std::runtime_error("message");
//            }
        }
        else if (strcmp(argv[i],"--print")){
            check_mode_already(mode,argv[i]);
            mode = do_print;
        }
        else if(strcmp(argv[i],"--pretty-print")){
            check_mode_already(mode,argv[i]);
            mode = do_pretty_print;
        }
        
        else if(strcmp(argv[i],"")==0){
            continue;
        }
        else{
            cerr<<"bad flag"<<argv[i]<<", try another"<<endl;
            exit(1);
        }
    }
    return mode;
}
                
static void check_mode_already(run_mode_t mode, std::string flag){
    if(mode!= do_nothing){
        std::cerr << "extra flag: "<<flag<<"\n";
        exit(1);
    }
}


