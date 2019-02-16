//
// Created by peter on 01/02/19.
//

#ifndef TEXTTEMPLATE_PRINTER_H
#define TEXTTEMPLATE_PRINTER_H

#include <iostream>

namespace print {

    template<typename T>
    void print(T p) {
        std::cout << p << std::endl;
    }

    template<typename T>
    void iter(T iter) {
        for (const auto &x : iter) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    template<typename T>
    void nestedIter(T nestedIter) {
        for (const auto &x : nestedIter) {
            iter(x);
        }
    }

}


#endif //TEXTTEMPLATE_PRINTER_H
