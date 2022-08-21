#pragma once

#ifndef NDEBUG

#include <iostream>

#define DEBUG_LOG(STR) std::cout << STR + '\n';

#else
#define DEBUG_LOG(STR);
#endif