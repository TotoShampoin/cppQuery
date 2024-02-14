#include "cppQuery.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>
#include <format>
#include <stdexcept>
#include <string>

using namespace emscripten;

EMSCRIPTEN_BINDINGS( EventBinding ) {
	emscripten::class_<std::function<void(emscripten::val e)> >( "ListenerCallback" )
	    .constructor<>()
	    .function("onload", &std::function<void(emscripten::val e)>::operator() );
};


void $::_createElement(const std::string& html_string) {
    $element = val::global("document").call<val>("createElement", std::string("div"));
    $element.set("innerHTML", html_string);
    $element = $element["firstElementChild"];
}
void $::_queryElement(const std::string& query_selector) {
    $element = val::global("document").call<val>("querySelector", query_selector);
    if($element.isUndefined()) {
        throw std::runtime_error(std::format("\"{}\" does not exist", query_selector));
    }
}

$::$(const std::string& query_selector) {
    if(query_selector.find('<') != std::string::npos) {
        _createElement(query_selector);
    } else {
        _queryElement(query_selector);
    }
}

$::~$() {
}

emscripten::val& $::get() {
    return $element;
}

std::string $::html() const {
    return $element["innerHTML"].as<std::string>();
}

$& $::html(const std::string& html_content) {
    $element.set("innerHTML", html_content);
    return *this;
}
std::string $::text() const {
    return $element["textContent"].as<std::string>();
}

$& $::text(const std::string& text_content) {
    $element.set("textContent", text_content);
    return *this;
}

std::string $::attr(const std::string& attribute) const {
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

bool $::hasClass(const std::string& class_name) const {
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

$& $::append(const $& other) {
    $element.call<void>("append", other.$element);
    return *this;
}

$& $::prepend(const $& other) {
    $element.call<void>("prepend", other.$element);
    return *this;
}

$& $::on(const std::string& event_name, const std::function<void(emscripten::val)>& callback_cpp) {
    auto callback_js = emscripten::val(callback_cpp)["onload"].call<emscripten::val>("bind", callback_cpp);
    $element.call<void>("addEventListener", event_name, callback_js);
    return *this;
}