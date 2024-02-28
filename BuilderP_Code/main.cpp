#include <iostream>
#include "Person.hpp"
#include "PersonBuilder.hpp"
using namespace std;

int main()
{
    Person person = Person::create("Dany")
                                .lives()
                                .at("111 Road")
                                .with_postcode("84000")
                                .in("XYZ")
                                .works()
                                .with("TestSoft")
                                .as_a("Developer")
                                .earning("000");
    
    
    cout << person << endl;
    
    return 0;
}
