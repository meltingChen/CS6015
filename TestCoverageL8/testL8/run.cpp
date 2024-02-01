extern "C" {
#include "run.hpp"
};
#define CATCH_CONFIG_RUNNER
#include "../TestCoverageL8/catch.h"
bool run_tests() {
const char *argv[] = { "test" };
return (Catch::Session().run(1, argv) == 0);
}
