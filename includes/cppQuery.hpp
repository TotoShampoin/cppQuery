#pragma once

#include <functional>
#include <string>
#include <emscripten/bind.h>

class $ {
public:
    $(const std::string&);
    ~$();

    emscripten::val& get();

    std::string html();
    $& html(const std::string&);

    std::string text();
    $& text(const std::string&);

    std::string attr(const std::string&);
    $& attr(const std::string&, const std::string&);

    $& addClass(const std::string&);
    $& removeClass(const std::string&);
    bool hasClass(const std::string&);

    $& append(const std::string&);
    $& prepend(const std::string&);

    $& on(const std::string&, const std::function<void(emscripten::val)>&);
private:
    emscripten::val $element;

    void _createElement(const std::string&);
    void _queryElement(const std::string&);
};
