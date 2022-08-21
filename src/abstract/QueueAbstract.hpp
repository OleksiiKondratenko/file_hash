#pragma once

namespace file_hash {
namespace abstract {

template<typename T>
class QueueAbstract {
public:
    virtual bool popTry(T &t) = 0;
    virtual void popWait(T &t) = 0;
    virtual void pushWait(T const &t) = 0;
};

}
}