#pragma once

#include <functional>
#include <string>
#include <emscripten/bind.h>

class $ {
public:
    $(const std::string&);
    ~$();

    emscripten::val& get();

    std::string html() const;
    $& html(const std::string&);

    std::string text() const;
    $& text(const std::string&);

    std::string val() const;
    $& val(const std::string&);

    std::string attr(const std::string&) const;
    $& attr(const std::string&, const std::string&);
    $& removeAttr(const std::string&);

    $& addClass(const std::string&);
    $& removeClass(const std::string&);
    bool hasClass(const std::string&) const;

    $& css(const std::string&, const std::string&);
    std::string css(const std::string&) const;

    $& hide();
    $& show();
    $& toggle();

    $& append(const std::string&);
    $& prepend(const std::string&);
    $& append(const $&);
    $& prepend(const $&);

    $& on(const std::string&, const std::function<void(emscripten::val)>&);
    $& off(const std::string&);
    $& trigger(const std::string&);

    // $ clone() const;
    // std::vector<$> children() const;
    // $ parent() const;

private:
    emscripten::val $element;

    void _createElement(const std::string&);
    void _queryElement(const std::string&);
};
