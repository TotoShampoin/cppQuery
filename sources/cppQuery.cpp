#include "cppQuery.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>
#include <format>
#include <stdexcept>
#include <string>

constexpr const char* ID_NAME = "wasm-id";
using namespace emscripten;

$::$(const std::string& query_selector) {
    $element = val::global("document").call<val>("querySelector", query_selector);
    if($element.isUndefined()) {
        throw std::runtime_error(std::format("\"{}\" does not exist", query_selector));
    }
}

$::~$() {
}

emscripten::val& $::get() {
    return $element;
}

std::string $::html() {
    return $element["innerHTML"].as<std::string>();
}

$& $::html(const std::string& html_content) {
    $element.set("innerHTML", html_content);
    return *this;
}
std::string $::text() {
    return $element["textContent"].as<std::string>();
}

$& $::text(const std::string& text_content) {
    $element.set("textContent", text_content);
    return *this;
}

std::string $::attr(const std::string& attribute) {
    return $element.call<std::string>("getAttribute", attribute);
}

$& $::attr(const std::string& attribute, const std::string& value) {
    $element.call<void>("setAttribute", attribute, value);
    return *this;
}

$& $::addClass(const std::string& class_name) {
    $element["classList"].call<void>("add", class_name);
    return *this;
}

$& $::removeClass(const std::string& class_name) {
    $element["classList"].call<void>("remove", class_name);
    return *this;
}

bool $::hasClass(const std::string& class_name) {
    return $element["classList"].call<bool>("contains", class_name);
}

$& $::append(const std::string& html_content) {
    $element.set("innerHTML", $element["innerHTML"].as<std::string>() + html_content);
    return *this;
}

$& $::prepend(const std::string& html_content) {
    $element.set("innerHTML", html_content + $element["innerHTML"].as<std::string>());
    return *this;
}