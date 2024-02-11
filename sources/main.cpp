#include "cppQuery.hpp"
#include <iostream>


int main(int argc, const char* argv[]) {
    std::cout << $("#element").html() << "\n";
    
    $("#element")
        .html("<p>:)</p>")
        .addClass("blue");

    return 0;
}
