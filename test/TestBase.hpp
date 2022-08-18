#pragma once

#include <string>

class TestBase {
public:
    const std::string &getName() { return m_name; }

    virtual bool run() = 0;
protected:
    TestBase(std::string &&name) : m_name(std::forward<std::string>(name)) {}
private:
    const std::string m_name;
};