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

class SetLedState : public Command{
public:
    SetLedState(const LedState state) : state_{state} {}

    virtual std::string execute(LedDriver &ledDriver) const override final {
        ledDriver.set_state(state_);
        return "OK";
    }

    LedState state_;
};

}
}


