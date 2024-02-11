#pragma once

#include <string>
#include <emscripten/bind.h>

class $ {
public:
    $(const std::string& query_selector);
    ~$();

    emscripten::val& get();

    std::string html();
    $& html(const std::string&);

    std::string text();
    $& text(const std::string&);

    std::string attr(const std::string& attribute);
    $& attr(const std::string& attribute, const std::string& value);

    $& addClass(const std::string& className);
    $& removeClass(const std::string& className);
    bool hasClass(const std::string& className);

    $& append(const std::string& htmlContent);
    $& prepend(const std::string& htmlContent);
private:
    emscripten::val $element;
};
