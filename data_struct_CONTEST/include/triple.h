#ifndef HPGDA_SPRING22_TRIPLE_H
#define HPGDA_SPRING22_TRIPLE_H
#include <iostream>

class triple {
public:
    long x;
    long y;
    double val;

    bool operator<(const triple &other) const {
        if (x < other.x) return true;
        if (other.x < x) return false;
        if (y < other.y) return true;
        if (other.y < y) return false;
        return val < other.val;
    }
};

#endif //HPGDA_SPRING22_TRIPLE_H
