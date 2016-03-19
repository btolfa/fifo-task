/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 19.03.16
 * 
 */

#pragma once 

#include <ostream>

namespace fifoserver {

enum class LedColor {
    red,
    green,
    blue
};

inline std::ostream& operator<<(std::ostream& os, const LedColor & color) {
    switch (color) {
        case LedColor::red:
            os << "red";
            break;
        case LedColor::green:
            os << "green";
            break;
        case LedColor::blue:
            os << "blue";
            break;
    }

    return os;
}

}