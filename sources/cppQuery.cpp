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

$& $::html(const std::string& html) {
    $element.set("innerHTML", html);
    return *this;
}
std::string $::text() {
    return $element["textContent"].as<std::string>();
}

$& $::text(const std::string& text) {
    $element.set("textContent", text);
    return *this;
}

std::string $::attr(const std::string& attribute) {
    return $element.call<std::string>("getAttribute", attribute);
}

$& $::attr(const std::string& attribute, const std::string& value) {
    $element.call<void>("setAttribute", attribute, value);
    return *this;
}

$& $::addClass(const std::string& className) {
    $element["classList"].call<void>("add", className);
    return *this;
}

$& $::removeClass(const std::string& className) {
    $element["classList"].call<void>("remove", className);
    return *this;
}

bool $::hasClass(const std::string& className) {
    return $element["classList"].call<bool>("contains", className);
}

$& $::append(const std::string& htmlContent) {
    $element.set("innerHTML", $element["innerHTML"].as<std::string>() + htmlContent);
    return *this;
}

$& $::prepend(const std::string& htmlContent) {
    $element.set("innerHTML", htmlContent + $element["innerHTML"].as<std::string>());
    return *this;
}