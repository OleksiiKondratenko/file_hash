#pragma once

#include "blocks/Block.hpp"

#include "abstract/QueueAbstract.hpp"
#include <boost/lockfree/queue.hpp>

namespace file_hash {
namespace lockFree {

class LockFreeQueue : public abstract::QueueAbstract<blocks::BlockPtr> {
public:
    bool popTry(blocks::BlockPtr &t) override;
    void popWait(blocks::BlockPtr &t) override;
    void pushWait(blocks::BlockPtr const &t) override;
private:
    boost::lockfree::queue<blocks::BlockPtr> m_queue{0};
};

}
}