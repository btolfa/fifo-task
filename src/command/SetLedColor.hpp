/**
 *
 * @author Tengiz Sharafiev<btolfa@gmail.com>
 * @date 27.03.16
 * 
 */

#pragma once

#include "Command.hpp"

namespace fifoserver {
namespace command {

class SetLedColor : public Command{
public:
    SetLedColor(const LedColor color) : color_{color} {}

    virtual std::string execute(LedDriver &ledDriver) const override final {
        if (ledDriver.is_enabled()) {
            ledDriver.set_color(color_);
            return "OK";
        } else {
            // Нельзя высталять цвет если LED не включен
            return "FAILED";
        }
    }

    LedColor color_;
};

}
}


