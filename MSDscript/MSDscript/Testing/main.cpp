//#define CATCH_CONFIG_MAIN
//#include "catch.h"
#define CATCH_CONFIG_RUNNER
#include "catch.h"
int main(int argc, char **argv) {
    Catch::Session().run(argc, argv);
    return 0;
}
