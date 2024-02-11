#include "cppQuery.hpp"

#include <emscripten.h>
#include <emscripten/em_asm.h>
#include <functional>
#include <sstream>
#include <string>

constexpr const char* ID_NAME = "wasm-id";

$::$(const std::string& query_selector) {
    size_t hashed = std::hash<std::string>()(query_selector);
    std::stringstream ss;
    ss << ID_NAME << "-" << std::hex << hashed;
    _id = ss.str();
    EM_ASM({
        const $element = document.querySelector(UTF8ToString($0));
        if(!$element) {
            throw `"${UTF8ToString($0)}" does not exist`;
        }
        $element.setAttribute(UTF8ToString($1), "");
    }, query_selector.c_str(), _id.c_str());
}

$::~$() {
    EM_ASM({
        const $element = document.querySelector(`[${UTF8ToString($0)}]`);
        $element.removeAttribute(UTF8ToString($0));
    }, _id.c_str());
}

std::string $::html() {
    int length = EM_ASM_INT({
        return document.querySelector(`[${UTF8ToString($0)}]`).innerHTML.length;
    }, _id.c_str());
    auto html = std::vector<char>(length);
    EM_ASM({
        stringToUTF8(document.querySelector(`[${UTF8ToString($2)}]`).innerHTML, $0, $1);
    }, html.data(), length, _id.c_str());
    return html.data();
}

$& $::html(const std::string& html) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($1)}]`).innerHTML = UTF8ToString($0);
    }, html.c_str(), _id.c_str());
    return *this;
}

std::string $::text() {
    int length = EM_ASM_INT({
        return document.querySelector(`[${UTF8ToString($0)}]`).textContent.length;
    }, _id.c_str());
    auto text = std::vector<char>(length);
    EM_ASM({
        stringToUTF8(document.querySelector(`[${UTF8ToString($2)}]`).textContent, $0, $1);
    }, text.data(), length, _id.c_str());
    return text.data();
}

$& $::text(const std::string& text) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($1)}]`).textContent = UTF8ToString($0);
    }, text.c_str(), _id.c_str());
    return *this;
}

std::string $::attr(const std::string& attribute) {
    int length = EM_ASM_INT({
        return document.querySelector(`[${UTF8ToString($0)}]`).getAttribute(UTF8ToString($1)).length;
    }, _id.c_str(), attribute.c_str());
    auto attr = std::vector<char>(length);
    EM_ASM({
        stringToUTF8(document.querySelector(`[${UTF8ToString($3)}]`).getAttribute(UTF8ToString($2)), $0, $1);
    }, attr.data(), length, attribute.c_str(), _id.c_str());
    return attr.data();
}

$& $::attr(const std::string& attribute, const std::string& value) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($2)}]`).setAttribute(UTF8ToString($0), UTF8ToString($1));
    }, attribute.c_str(), value.c_str(), _id.c_str());
    return *this;
}

$& $::addClass(const std::string& className) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($1)}]`).classList.add(UTF8ToString($0));
    }, className.c_str(), _id.c_str());
    return *this;
}

$& $::removeClass(const std::string& className) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($1)}]`).classList.remove(UTF8ToString($0));
    }, className.c_str(), _id.c_str());
    return *this;
}

bool $::hasClass(const std::string& className) {
    return EM_ASM_INT({
       return document.querySelector(`[${UTF8ToString($1)}]`).classList.contains(UTF8ToString($0));
    }, className.c_str(), _id.c_str());
}

$& $::append(const std::string& htmlContent) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($1)}]`).innerHTML += UTF8ToString($0);
    }, htmlContent.c_str(), _id.c_str());
    return *this;
}

$& $::prepend(const std::string& htmlContent) {
    EM_ASM({
       document.querySelector(`[${UTF8ToString($1)}]`).innerHTML = UTF8ToString($0) + document.querySelector(`[${UTF8ToString($1)}]`).innerHTML;
    }, htmlContent.c_str(), _id.c_str());
    return *this;
}
