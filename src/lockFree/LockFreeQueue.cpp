#include "LockFreeQueue.hpp"

using namespace file_hash::lockFree;
using namespace file_hash::abstract;

bool LockFreeQueue::popTry(blocks::BlockPtr &t)
{
    return m_queue.pop(t);
}

void LockFreeQueue::popWait(blocks::BlockPtr &t)
{
    while (!m_queue.pop(t));
}

void LockFreeQueue::pushWait(blocks::BlockPtr const &t)
{
    while (!m_queue.push(t));
}