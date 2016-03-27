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
    SetLedColor(const LedState state) : state_{state} {}

    virtual std::string execute(LedDriver &ledDriver) const override final {
        return {};
    }
private:
    LedState state_;
};

}
}


