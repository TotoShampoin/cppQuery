#include "cppQuery.hpp"
#include <iostream>


int main(int argc, const char* argv[]) {
    auto $element = $("#element");
    std::cout << $element.html() << "\n";
    
    $element
        .html("<p>:)</p>")
        .addClass("blue")
        .removeClass("red")
        .prepend("<h1>hewo</h1>")
        .attr("contenteditable", "true");

    return 0;
}
