#include "cppQuery.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>
#include <format>
#include <stdexcept>
#include <string>

using JSObj = emscripten::val;

EMSCRIPTEN_BINDINGS( EventBinding ) {
	emscripten::class_<std::function<void(JSObj e)> >( "ListenerCallback" )
	    .constructor<>()
	    .function("onload", &std::function<void(JSObj e)>::operator() );
};


void $::_createElement(const std::string& html_string) {
    $element = JSObj::global("document").call<JSObj>("createElement", std::string("div"));
    $element.set("innerHTML", html_string);
    $element = $element["firstElementChild"];
}
void $::_queryElement(const std::string& query_selector) {
    $element = JSObj::global("document").call<JSObj>("querySelector", query_selector);
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
$::$(const JSObj& object) {
    // if object is not an HTML element, throw an error
    if(!object.instanceof(JSObj::global("HTMLElement"))) {
        throw std::runtime_error("Not an HTML element");
    }
    $element = object;
}
$::~$() {}

JSObj& $::get() {
    return $element;
}
const JSObj& $::get() const {
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

std::string $::val() const {
    return $element["value"].as<std::string>();
}

$& $::val(const std::string& value) {
    $element.set("value", value);
    return *this;
}

std::string $::attr(const std::string& attribute) const {
    return $element.call<std::string>("getAttribute", attribute);
}
$& $::attr(const std::string& attribute, const std::string& value) {
    $element.call<void>("setAttribute", attribute, value);
    return *this;
}
$& $::removeAttr(const std::string& attribute) {
    $element.call<void>("removeAttribute", attribute);
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

$& $::css(const std::string& property, const std::string& value) {
    $element["style"].set(property, value);
    return *this;
}
std::string $::css(const std::string& property) const {
    return $element["style"][property].as<std::string>();
}

$& $::hide() {
    return css("display", "none");
}
$& $::show() {
    return css("display", "");
}
$& $::toggle() {
    return css("display") == "none" ? show() : hide();
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

$& $::on(const std::string& event_name, const std::function<void(JSObj)>& callback_cpp) {
    auto callback_js = JSObj(callback_cpp)["onload"].call<JSObj>("bind", callback_cpp);
    $element.call<void>("addEventListener", event_name, callback_js);
    return *this;
}
$& $::off(const std::string& event_name) {
    $element.call<void>("removeEventListener", event_name);
    return *this;
}
$& $::trigger(const std::string& event_name) {
    auto event = JSObj::global("Event").new_(event_name);
    $element.call<void>("dispatchEvent", event);
    return *this;
}

$ $::clone() const {
    return $($element.call<JSObj>("cloneNode", true));
}
std::vector<$> $::children() const {
    std::vector<$> children;
    auto children_js = $element["children"];
    for(int i = 0; i < children_js["length"].as<int>(); i++) {
        children.push_back($(children_js[i]));
    }
    return children;
}

$ $::parent() const {
    return $($element["parentNode"]);
}
