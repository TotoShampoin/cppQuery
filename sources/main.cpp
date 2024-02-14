#include "cppQuery.hpp"
#include <iostream>


EMSCRIPTEN_BINDINGS(events) {};

int main(int argc, const char* argv[]) {
    auto $element = $("#element");
    std::cout << $element.html() << "\n";

    auto $img = $("<img src='https://totoshampoin.fr/assets/TotoShampoin_t.svg'>");

    std::cout << $img.attr("src") << "\n";
    
    $element
        .html("<p>:)</p>")
        .addClass("blue")
        .removeClass("red")
        .prepend("<h1>hewo</h1>")
        .append($img)
        .attr("contenteditable", "true")
        .on("click", [](emscripten::val e) {
            std::cout << "clicked\n";
        });

    return 0;
}
