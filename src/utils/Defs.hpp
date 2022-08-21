#pragma once

#define NO_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#define NO_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define NO_COPY_MOVE(Class) \
    NO_COPY(Class) \
    NO_MOVE(Class)
