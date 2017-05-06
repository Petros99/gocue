#ifndef DEBUG_H
#define DEBUG_H
#ifdef DEBUG
#include <iostream>
#define void dprintf(cost char * output) {
    std::cout << __FILE__ << "(" << __LINE__ << ") DEBUG: " << output << std::endl;
}
#else
#define dout 0 && std::cout
#endif
#endif // DEBUG_H
