#include "Book.hpp"
#include <cstring>

// HELPERS
namespace {
    template <typename T>
    void mySwap(T& first, T& second){
        T temp = first;
        first = second;
        second = temp;
    }
}

