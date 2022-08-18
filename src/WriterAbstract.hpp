#pragma once

#include <ostream>

class WriterAbstract {
public:
    virtual void putNext(const char *data) = 0;
};