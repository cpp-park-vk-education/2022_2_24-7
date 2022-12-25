#pragma once
#include <string>

struct Element {
    Element(const char* value, const size_t* count, const size_t* UserId)
        : _value(*value), count(*count), UserId(*UserId), isVisible(true), next(nullptr){};

    char _value;
    size_t count;
    size_t UserId;
    bool isVisible;

    Element* next;
};
