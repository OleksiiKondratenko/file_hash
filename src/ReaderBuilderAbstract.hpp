#pragma once

#include <tuple>

#include "ReaderAbstract.hpp"

class ReaderBuilderAbstract {
public:
    virtual ~ReaderBuilderAbstract() = default;

    virtual ReaderAbstract &&getReader() = 0;
};
