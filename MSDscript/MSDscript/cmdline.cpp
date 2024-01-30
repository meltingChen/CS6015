//
//  cmdline.cpp
//  MSDscript
//
//  Created by 陳肜樺 on 1/14/24.
//

#define CATCH_CONFIG_RUNNER
#include "cmdline.hpp"
#include <cstring>
#include <cstdlib>


using namespace std;
void use_arguments(int argc,const char * argv[]){
    bool testTracker = false;// bool
    
    for(int i =1 ;i<argc;i++){
        
        if(strcmp(argv[i],"--help")==0){
            cout<<"Available flags:"<<endl;
            cout<<"--test :run tests"<<endl;
            cout<<"--help : this help"<<endl;
            exit(0);
        }
        else if(strcmp(argv[i],"--test")==0){
            if(testTracker!=true){
                
                if( Catch::Session().run(1, argv)!=0){
                    std::cerr << "Tests failed!" << std::endl;
                    exit(1);
                }
                else{
                    std::cout << "All tests passed!" << std::endl;
                    testTracker = true;
                }
                
            }
            else{
                cerr<<"Duplicate --test"<<endl;
                exit(1);
            }
        }
        
        else if(strcmp(argv[i],"--interp")==0){
            if (i + 1 < argc) {
                
                
            } else {
                throw std::runtime_error("message");
            }
        }
        
        else if(strcmp(argv[i],"")==0){
            continue;
        }
        else{
            cerr<<"bad flag"<<argv[i]<<", try another"<<endl;
            exit(1);
        }
    }
}


