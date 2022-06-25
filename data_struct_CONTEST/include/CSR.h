#ifndef HPGDA_SPRING22_CSR_H
#define HPGDA_SPRING22_CSR_H
#include <iostream>
#include <vector>
#include <functional>
#include <iostream>
#include "triple.h"

class CSR {

    long v, e;
    std::vector<long> col_idx, row_ptr;
    std::vector<double> value;

public:

    CSR(long v, long e) : v(v), e(e){}

    ~CSR(){
        col_idx.clear();
        row_ptr.clear();
        value.clear();
    }

    inline void populate(triple *edges){
        long row_count = 0, x;
        long i = 0;
        for(; i < e; i++){
            col_idx.push_back(edges[i].y);
            value.push_back(edges[i].val);

            x = edges[i].x;

            if (row_count != x) {
                do{
                    row_ptr.push_back(i);
                    row_count++;
                }while (row_count != x);
            }
        }

        for (; row_count < v; row_count++)
            row_ptr.push_back(i);

        finished();
    }

    inline std::vector<std::pair<long, double>> get_neighbors(long idx){

        long num_elem = row_ptr[idx] - row_ptr[idx-1];

        std::vector<std::pair<long, double>> ret_elems;
        long j = 0;

        for(long i = row_ptr[idx] - num_elem; j < num_elem; i++, j++)
            ret_elems.emplace_back(col_idx[i], value[i]);

        return ret_elems;
    }

    inline void finished(){};

};


#endif //HPGDA_SPRING22_CSR_H
